#include "CustomReg.hh"


namespace gem5
{

CustomRegisterBank::CustomRegisterBank(const std::string &name, Addr base)
    : RegisterBankLE(name, base),
      realPartReg("RealPartReg"),
      imagPartReg("ImagPartReg")
{
    // Add registers to the bank at specific offsets
    addRegister({0x0, imagPartReg});
    addRegister({0x4, realPartReg});//0x8 时候报错 ，不知道原因 按理说应该留足够空间？但是这样改对的逻辑好像是应该一个接一个不留空隙
}


}