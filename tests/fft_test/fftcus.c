#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#define N 2048

// 使用数组表示复数，其中 X[i=2k] 为实部，X[i=2k+1] 为虚部
float X[2 * N], *W;   // 输入序列和旋转因子
int size = 0;          // 数据长度
float PI = 4.0 * atan(1); // π的定义

void readFile() {
    FILE *file = fopen("/home/g/riscv/gem5/tests/fft_test/in.txt", "r");
    if (!file) {
        perror("文件打开失败");
        return;
    }

    // 读取文件并赋值给复数数组 X，实部存储在 X[2k]，虚部存储在 X[2k+1]
    int i = 0;
    while (fscanf(file, "%f%f", &X[2 * i], &X[2 * i + 1]) == 2) {
        i++;
    }
    size = i;
    fclose(file);

    printf("读取到 %d 个复数数据\n", size);
}

void output() {
    FILE *outfile = fopen("/home/g/riscv/gem5/tests/fft_test/out.txt", "w");
    if (!outfile) {
        perror("文件打开失败");
        return;
    }
    printf("开始保存\n");
    // 输出复数数据（X[2k]为实部，X[2k+1]为虚部）
    for (int i = 0; i < size; i++) {
        fprintf(outfile, "%.4f", X[2 * i]/sqrt(size));  // 输出实部/sqrt(size)
        if (X[2 * i + 1] >= 0) {
            fprintf(outfile, "+%.4fj\n", X[2 * i + 1]/sqrt(size));
        } else {
            fprintf(outfile, "%.4fj\n", X[2 * i + 1]/sqrt(size));
        }
    }
    fclose(outfile);
    printf("傅里叶变换结果已保存到文件：\n");
}

void change() {
    int i = 0, j = 0, k = 0;
    float t;

    for (i = 0; i < size; i++) {
        k = i;
        j = 0;
        t=(log(size)/log(2));
        while ((t--) > 0) {
            j = j << 1;
            j |= (k & 1);
            k = k >> 1;
        }
        if (j > i) {
            // 交换 X[i] 和 X[j]
            float temp_real = X[2 * i];
            float temp_imag = X[2 * i + 1];
            X[2 * i] = X[2 * j];
            X[2 * i + 1] = X[2 * j + 1];
            X[2 * j] = temp_real;
            X[2 * j + 1] = temp_imag;
        }
    }
}

void transform() {
    int i;
    W = (float *)malloc(2 * sizeof(float) * size); // W数组存储旋转因子的实部和虚部
    for (i = 0; i < size; i++) {
        W[2 * i] = cos(2 * PI / size * i);    // 实部
        W[2 * i + 1] = -sin(2 * PI / size * i); // 虚部
    }
}

void add(float a_real, float a_imag, float b_real, float b_imag, float *c_real, float *c_imag) {
    *c_real = a_real + b_real;
    *c_imag = a_imag + b_imag;
}

void sub(float a_real, float a_imag, float b_real, float b_imag, float *c_real, float *c_imag) {
    *c_real = a_real - b_real;
    *c_imag = a_imag - b_imag;
}

void mul(float a_real, float a_imag, float b_real, float b_imag, float *c_real, float *c_imag) {
    float a[2]={a_real,a_imag};
    float b[2]={b_real,b_imag};
    float c[2]={0};
    __asm__ volatile (
        "vle32.v v0, (%[pa])\n\t"               // 加载 a 数组到 v0 寄存器
        "vle32.v v1, (%[pb])\n\t"               // 加载 b 数组到 v1 寄存器
        "vfwcmul.vv v2, v0, v1\n\t"
        "vse32.v v2, (%[pc])\n\t"               // 将结果从 v2 寄存器存储到 result 数组
        :
        : [pa] "r" (a),
          [pb] "r" (b),
          [pc] "r" (c)
        : "v0", "v1", "v2"  // 使用的寄存器
    );
    *c_real = c[0];
    *c_imag = c[1];
}

void fft() {
    int i = 0, j = 0, k = 0, m = 0;
    float q_real, q_imag, y_real, y_imag, z_real, z_imag;
    change();
    for (i = 0; i < log(size) / log(2); i++) {
        m = 1 << i;
        for (j = 0; j < size; j += 2 * m) {
            for (k = 0; k < m; k++) {
                mul(X[2 * (k + j + m)], X[2 * (k + j + m) + 1], W[2 * k * size / (2 * m)], W[2 * k * size / (2 * m) + 1], &q_real, &q_imag);
                add(X[2 * (j + k)], X[2 * (j + k) + 1], q_real, q_imag, &y_real, &y_imag);
                sub(X[2 * (j + k)], X[2 * (j + k) + 1], q_real, q_imag, &z_real, &z_imag);
                X[2 * (j + k)] = y_real;
                X[2 * (j + k) + 1] = y_imag;
                X[2 * (j + k + m)] = z_real;
                X[2 * (j + k + m) + 1] = z_imag;
            }
        }
    }
}

int main() {
    __asm__ volatile(
        "vsetvli t0, %0, e32, m1\n"    // 设置向量长度为2，元素大小为32位
        : // No outputs
        : "r" (2)  // 输入参数：N，设置向量长度
        : "t0"  // 使用的寄存器
    );
    readFile();
    transform(); // 生成旋转因子
    fft();       // 执行 FFT 变换
    output();    // 输出结果
    return 0;
}
