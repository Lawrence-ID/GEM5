// test_reg_add.c
#include <stdio.h>

int main(){
    int a, b, c;
    a = 3;  // Rs1 的值
    b = 2;  // Rs2 的值

    asm volatile
    (
        "reg_add   %[z], %[x], %[y]\n\t"
        : [z] "=r" (c)
        : [x] "r" (a), [y] "r" (b)
    );

    // 使用与 decoder.isa 中相同的常量值
    // int twc = 2; // 假设在 decoder.isa 中 twc 被定义为 2
    // int tws = 3; // 假设在 decoder.isa 中 tws 被定义为 3

    // 计算期望的结果
    //int expected = (a * 2) + (b * 3);

    // 验证结果
    if ( c != 12 ){
        printf("%d\n", c);
        printf("\n[[FAILED]]\n");
        return -1;
    }

    printf("\n[[PASSED]]\n");
    return 0;
}

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
