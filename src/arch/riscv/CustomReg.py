from m5.params import *
from m5.SimObject import SimObject

class CustomRegisterBank(SimObject):
    type = 'CustomRegisterBank'
    cxx_class = 'gem5::CustomRegisterBank'
    cxx_header = "arch/riscv/CustomReg.hh"

    # 定义寄存器的参数
    #initial_value = Param.UInt32(0, "Initial 32-bit value of the custom register")
    #initial_value = Param.UInt64(0, "Initial value of the custom register")