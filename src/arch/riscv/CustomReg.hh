#ifndef __ARCH_RISCV_REGS_CUSTOMREG_HH__
#define __ARCH_RISCV_REGS_CUSTOMREG_HH__

#include "dev/reg_bank.hh"



namespace gem5
{

class CustomRegisterBank : public RegisterBankLE {
public:
    //CustomReg() : RegisterBase(/*寄存器大小*/ 32, /*默认值*/ 0) {}
    CustomRegisterBank(const std::string &name, Addr base);//报错
    Register32 realPartReg;
    Register32 imagPartReg;
/*
    int value = 0;
    uint32_t read()  {
        return value;
    }
    void write(uint32_t data)  {
        value = data;
    }
*/
};
}

#endif // __ARCH_RISCV_REGS_CUSTOMREG_HH__