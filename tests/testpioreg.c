#include <stdio.h>
#include <stdint.h>
#include "../src/arch/riscv/PioReg.hh"




//#define FIRST_PIO_REG_ADDR 0x20000000
//volatile uint32_t *pio_reg = (uint32_t *)FIRST_PIO_REG_ADDR;

// uint32_t pio_reg_addr __attribute__((section(".pio_section"))) = 0x20000000;
#define PIO_REG 0x20000000
volatile uint32_t *PIO_REG_ADDR = (volatile uint32_t *) PIO_REG;

int main() {
    // volatile uint32_t *reg = (volatile uint32_t *) &pio_reg_addr;
    *PIO_REG_ADDR = 0x12345678;
    printf("Wrote 0x12345678 to PioReg at 0x20000000\n");

    /* 读取并打印 */
    uint32_t value = *PIO_REG_ADDR;
    printf("Read 0x%08x from PioReg\n", value);

    return 0;

    // // 写入寄存器
    // *pio_reg = 42;//测试
    // printf("Writing value 42 to the register...\n");

    // // 读取寄存器
    // uint32_t test_value = *pio_reg;
    // printf("Read value from register: %u\n", test_value);

    // return 0;
}




// #include <stdio.h>
// #include <stdint.h>
// #include <fcntl.h>
// #include <sys/mman.h>
// #include <unistd.h>

// #define PIO_REG_ADDR 0x20000000  // 寄存器基地址
// #define PIO_REG_SIZE 0x4         // 寄存器大小（4字节）

// int main() {
//     int fd = open("/dev/mem", O_RDWR | O_SYNC);
//     if (fd < 0) {
//         perror("open");
//         return -1;
//     }

//     // 内存映射
//     uint32_t *pio_reg = (uint32_t *)mmap(NULL, PIO_REG_SIZE, PROT_READ | PROT_WRITE,
//                                          MAP_SHARED, fd, PIO_REG_ADDR);
//     if (pio_reg == MAP_FAILED) {
//         perror("mmap");
//         close(fd);
//         return -1;
//     }

//     // 写寄存器
//     *pio_reg = 0x12345678;
//     printf("Wrote 0x12345678 to PIO_REG\n");

//     // 读寄存器
//     uint32_t value = *pio_reg;
//     printf("Read 0x%08x from PIO_REG\n", value);

//     // 清理
//     munmap(pio_reg, PIO_REG_SIZE);
//     close(fd);

//     return 0;
// }