from m5.params import *
from m5.params import Param, Addr, Latency
from m5.SimObject import SimObject
from m5.objects.PciDevice import PciDevice
from m5.SimObject import Parent  # 导入 Parent
from m5.objects import *
from m5.proxy import *
#from m5.objects import BasicPioDevice
# from m5.objects.BasicPioDevice import BasicPioDevice
from m5.objects.Device import BasicPioDevice
from m5.SimObject import SimObject

class PioReg(BasicPioDevice):
    type = 'PioReg'
    cxx_header = "arch/riscv/PioReg.hh"
    cxx_class = 'gem5::PioReg'


    # 定义参数
    pio_addr = Param.Addr("Base address of the register")
    pio_size = Param.Unsigned(4, "Size of the register in bytes")
    pio_latency = Param.Latency('1ns', "Programmed I/O latency")
    system = Param.System(Parent.any, "System we belong to")  # 新增：系统参数