// test_reg_add.c
#include <stdio.h>
#include <stdint.h>
#include<math.h>
#include<stdlib.h>
#include <riscv_vector.h>

int main(){
    // 初始化测试数据
    float source[8] = {1.0, 2.0, 3.0, 4.0};
    float dest[8] = {0.0, 0.0, 0.0, 0.0};

    // 使用内联汇编测试vslideup.vi指令
    asm volatile (
        "vsetvli t0, %[vl], e32, m1\n\t"    // 设置向量长度和元素宽度
        "vle32.v v0, (%[ps])\n\t"           // 加载source数组到v0寄存器
        "vle32.v v1, (%[pd])\n\t"           // 加载dest数组到v1寄存器
        "vslideup.vi v1, v0, 2\n\t"         // 将v0中的元素向上滑动2个位置，结果存入v1
        "vse32.v v1, (%[pd])\n\t"           // 将结果存回dest数组
        :
        : [ps] "r" (source),
          [pd] "r" (dest),
          [vl] "r" (4)
        : "t0", "v0", "v1"
    );

    // 打印结果
    printf("Source array: ");
    for(int i = 0; i < 4; i++) {
        printf("%.1f ", source[i]);
    }
    printf("\n");

    printf("Result after vslideup.vi: ");
    for(int i = 0; i < 4; i++) {
        printf("%.1f ", dest[i]);
    }
    printf("\n");

    return 0;

    // //测试自定义复数向量指令（vfwcmulu.vv）//经过测试最多4个元素？？？
    // float A[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    // float B[8] = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5};
    // float result[8];
    // // 将数组加载到向量寄存器
    // vfloat32m1_t va = vle32_v_f32m1(A);   // 加载A数组到向量
    // vfloat32m1_t vb = vle32_v_f32m1(B);   // 加载B数组到向量


    // float a[2] = {1,2};
    // float b[2] = {6,5};
    // float result[2] = {0};
    // asm volatile (
    //     "vsetvli t0, %[vl], e32, m1\n\t"    // 设置向量长度到t0寄存器和元素宽度
    //     "vle32.v v0, (%[pa])\n\t"               // 加载a数组到v0寄存器
    //     "vle32.v v1, (%[pb])\n\t"               // 加载b数组到v1寄存器
    //     "vfwcmul.vv v2, v0, v1\n\t"         // vwcmul自定义指令，结果存到v2
    //     "vse32.v v2, (%[pr])\n\t"               // 将结果从v2寄存器存储到result数组 这里也要同步修改
    //     :
    //     : [pa] "r" (a),
    //       [pb] "r" (b),
    //       [pr] "r" (result),
    //       [vl] "r" (2)
    //     : "t0", "v0", "v1", "v2"
    // );

    // printf("Result: ");
    // for(int i = 0; i < 2; i++) {
    //     printf("%.4f ", result[i]);
    // }
    // printf("\n");
    // return 0;
}

    // //测试自定义复数向量指令（vwcmulu.vv）是否可用——测试
    // float a[4] = {1,2,3,4,};
    // float b[4] = {4,3,2,1,};
    // double result[4] = {0};//测试宽化相关的指令时，应该使用对应的宽化数据类型！！！int32_t 或者int8_t

    // asm volatile (
    //     "vsetvli t0, %[vl], e32, m1\n\t"    // 设置向量长度到t0寄存器和元素宽度
    //     "vle32.v v0, (%[pa])\n\t"               // 加载a数组到v0寄存器
    //     "vle32.v v1, (%[pb])\n\t"               // 加载b数组到v1寄存器
    //     "vfwcmul.vv v2, v0, v1\n\t"         // vwcmul自定义指令，结果存到v2
    //     "vse64.v v2, (%[pr])\n\t"               // 将结果从v2寄存器存储到result数组 这里也要同步修改
    //     :
    //     : [pa] "r" (a),
    //       [pb] "r" (b),
    //       [pr] "r" (result),
    //       [vl] "r" (4)
    //     : "t0", "v0", "v1", "v2"
    // );

    // printf("Result: ");
    // for(int i = 0; i < 4; i++) {
    //     printf("%lf ", result[i]);
    // }
    // printf("\n");

    // return 0;