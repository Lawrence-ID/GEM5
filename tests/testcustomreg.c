// #include <stdio.h>
// #include <stdint.h>

// #define REAL_REG_ADDR 0x00
// #define IMAG_REG_ADDR 0x04

// int main() {
//     volatile uint64_t *real_reg = (uint64_t *)REAL_REG_ADDR;
//     volatile uint64_t *imag_reg = (uint64_t *)IMAG_REG_ADDR;

//     // 写入值到自定义寄存器
//     *real_reg = 10;
//     *imag_reg = 20;

//     // 从自定义寄存器读取值
//     uint64_t real_value = *real_reg;
//     uint64_t imag_value = *imag_reg;

//     // 输出寄存器的值
//     printf("Real Part: %lu\n", real_value);
//     printf("Imaginary Part: %lu\n", imag_value);

//     return 0;
// }



#include <stdint.h>
#include <stdio.h>

int main() {
    // 定义两个变量，用于存储寄存器值
    uint32_t reg_value_r = 0;
    uint32_t reg_value_i = 0;

    // 写入寄存器（ 0x0 和 0x4 是内存映射的地址）
    asm volatile (
        "li t0, 0x12345678\n"  // 将数据加载到寄存器 t0
        "sw t0, 0x0(%0)\n"     // 将 t0 的值存储到地址 0x0
        :
        : "r" (0x0)            // 基地址（伪装成操作数传入）
        : "t0"                 // 告诉编译器 t0 被修改
    );

    asm volatile (
        "li t1, 0x87654321\n"  // 将数据加载到寄存器 t1
        "sw t1, 0x4(%0)\n"     // 将 t1 的值存储到地址 0x4
        :
        : "r" (0x0)            // 基地址（伪装成操作数传入）
        : "t1"                 // 告诉编译器 t1 被修改
    );

    // 读取寄存器值
    asm volatile (
        "lw %0, 0x0(%1)\n"     // 从地址 0x0 读取到变量 reg_value_0
        : "=r" (reg_value_r)
        : "r" (0x0)
    );

    asm volatile (
        "lw %0, 0x4(%1)\n"     // 从地址 0x8 读取到变量 reg_value_8
        : "=r" (reg_value_i)
        : "r" (0x0)
    );

    // 打印寄存器值
    printf("Value at 0x0: 0x%08x\n", reg_value_r);
    printf("Value at 0x4: 0x%08x\n", reg_value_i);

    return 0;
}

// #include <stdio.h>

// int main(){
//     int a, b, c;
//     a = 3;  // Rs1 的值
//     b = 2;  // Rs2 的值

//     asm volatile
//     (
//         // "reg_add   %[z], %[x], %[y]\n\t"
//         // : [z] "=r" (c)
//         // : [x] "r" (a), [y] "r" (b)

//     );

//     // 验证结果
//     if ( c != 12 ){
//         printf("%d\n", c);
//         printf("\n[[FAILED]]\n");
//         return -1;
//     }

//     printf("\n[[PASSED]]\n");
//     return 0;
// }