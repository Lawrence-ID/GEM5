// test_reg_add.c
#include <stdio.h>
#include <stdint.h>

int main(){
    //测试自定义复数向量指令（vwcmulu.vv）是否可用——测试
    int32_t a[8] = {1,2,3,4,5,6,7,8};
    int32_t b[8] = {8,7,6,5,4,3,2,1};
    int64_t result[8] = {0};//测试宽化相关的指令时，应该使用对应的宽化数据类型！！！int32_t 或者int8_t

    asm volatile (
        "vsetvli t0, %[vl], e32, m1\n\t"    // 设置向量长度到t0寄存器和元素宽度
        "vle32.v v0, (%[pa])\n\t"               // 加载a数组到v0寄存器
        "vle32.v v1, (%[pb])\n\t"               // 加载b数组到v1寄存器
        "vwcmul.vv v2, v0, v1\n\t"         // vwcmul(cj)自定义指令，结果存到v2
        "vse64.v v2, (%[pr])\n\t"               // 将结果从v2寄存器存储到result数组 这里也要同步修改
        :
        : [pa] "r" (a),
          [pb] "r" (b),
          [pr] "r" (result),
          [vl] "r" (8)
        : "t0", "v0", "v1", "v2"
    );

	printf("Result: ");
    for(int i = 0; i < 8; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}

//     //测试自定义向量指令或原本（vadd.vv）是否可用——测试成功
//     int16_t a[8] = {1,2,3,4,5,6,7,8};
//     int16_t b[8] = {8,7,6,5,4,3,2,1};
//     int16_t result[8] = {0};

//     asm volatile (
//         "vsetvli t0, %[vl], e16, m1\n\t"    // 设置向量长度到t0寄存器和元素宽度
//         "vle16.v v0, (%[pa])\n\t"               // 加载a数组到v0寄存器
//         "vle16.v v1, (%[pb])\n\t"               // 加载b数组到v1寄存器
//         "vmod.vv v2, v0, v1\n\t"         // vmod.vv：v0和v1逐元素mod，结果存到v2
//         "vse16.v v2, (%[pr])\n\t"               // 将结果从v2寄存器存储到result数组
//         :
//         : [pa] "r" (a),
//           [pb] "r" (b),
//           [pr] "r" (result),
//           [vl] "r" (8)
//         : "t0", "v0", "v1", "v2"
//     );

//     printf("Result: ");
//     for(int i = 0; i < 8; i++) {
//         printf("%d ", result[i]);
//     }
//     printf("\n");
//     return 0;
// }

//     asm volatile (
//         "vsetvli t0, %[vl], e16, m1\n\t"    // 设置向量长度到t0寄存器和元素宽度
//         "vle16.v v0, (%[pa])\n\t"               // 加载a数组到v0寄存器
//         "vle16.v v1, (%[pb])\n\t"               // 加载b数组到v1寄存器
//         "vadd.vv v2, v0, v1\n\t"         // vadd.vv：v0和v1逐元素加法，结果存到v2
//         "vse16.v v2, (%[pr])\n\t"               // 将结果从v2寄存器存储到result数组
//         :
//         : [pa] "r" (a),
//           [pb] "r" (b),
//           [pr] "r" (result),
//           [vl] "r" (8)
//         : "t0", "v0", "v1", "v2"
//     );



//     printf("Result: ");
//     for(int i = 0; i < 8; i++) {
//         printf("%d ", result[i]);
//     }
//     printf("\n");
//     return 0;
// }

//     asm volatile (
//         "VADD_VV %[z], %[x], %[y]\n\t"
//             : [z]"=r" (result)
//             : [x]"r"(a), [y]"r"(b)
//             // : "v0", "v1", "v2"

//     );


//     //测试通用寄存器和自定义指令结合
//     int a, b, c;
//     a = 3;  // Rs1 的值
//     b = 2;  // Rs2 的值
//     int result;

//     asm volatile (
//         "ADDI cus, x0, 3\n\t"  // t0 = a
//         "ADDI t1, x0, 2\n\t"  // t1 = b
//         "reg_add %0, cus, t1\n\t"    // result = t0 + t1
//         : "=r" (result)              // 输出操作数
//         : "r" (a), "r" (b)    // 输入操作数
//         : "cus", "t1"                         // 被修改的寄存器
//     );

//     printf("Result: %d\n", result);
//     return 0;
// }


    // asm volatile
    // (
    //     "reg_add   %[z], %[x], %[y]\n\t"
    //     : [z] "=r" (c)
    //     : [x] "r" (a), [y] "r" (b)
    // );

    // 使用与 decoder.isa 中相同的常量值
    // int twc = 2; // 假设在 decoder.isa 中 twc 被定义为 2
    // int tws = 3; // 假设在 decoder.isa 中 tws 被定义为 3

    // 计算期望的结果
    //int expected = (a * 2) + (b * 3);

//     // 验证结果
//     if ( c != 12 ){
//         printf("%d\n", c);
//         printf("\n[[FAILED]]\n");
//         return -1;
//     }

//     printf("\n[[PASSED]]\n");
//     return 0;
// }

// modulus.c
// #include <stdio.h>
// int main(){
//  int a,b,c;
//     a = 5;
//     b = 2;
//  asm volatile
//     (
//  "reg_add   %[z], %[x], %[y]\n\t"
//     : [z] "=r" (c)
//     : [x] "r" (a), [y] "r" (b)
//     );
//  if ( c != 1 ){
//             printf("\n[[FAILED]]\n");
//  return -1;
//     }
//     printf("\n[[PASSED]]\n");
//  return 0;
// }
