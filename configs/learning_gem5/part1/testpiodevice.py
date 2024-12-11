
"""
This is the RISCV equivalent to `simple.py` (which is designed to run using the
X86 ISA). More detailed documentation can be found in `simple.py`.
"""

import m5
from m5.objects import *
from m5.objects import PioReg
import os

system = System()

# system.clk_domain = SrcClockDomain()
# system.clk_domain.clock = "1GHz"
# system.clk_domain.voltage_domain = VoltageDomain()
# 配置时钟频率
system.clk_domain = SrcClockDomain(clock="1GHz", voltage_domain=VoltageDomain())#简化写法

system.mem_mode = "timing"
system.mem_ranges = [
    AddrRange("1GB"),  # 系统内存范围
    # AddrRange(0x20000000, size=0x1000)  # PioReg 的地址范围，假设大小为 4KB
]

system.membus = SystemXBar()
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

# 添加PioReg设备
system.pio_reg = PioReg(pio_addr=0x20000000, pio_latency='10ns') #pioreg
system.pio_reg.pio = system.membus.mem_side_ports # 将寄存器连接到系统总线 mem_side_ports  响应--请求 端口

# system.membus.add_child(system.reg_device, range=AddrRange(0x10000000, size="1kB"))

system.cpu = RiscvTimingSimpleCPU()
system.cpu.icache_port = system.membus.cpu_side_ports
system.cpu.dcache_port = system.membus.cpu_side_ports

system.cpu.createInterruptController()



system.system_port = system.membus.cpu_side_ports

thispath = os.path.dirname(os.path.realpath(__file__))
# binary = os.path.join(
#     thispath,
#     "../../../",
#     "tests/test-progs/hello/bin/riscv/linux/hello",
# )
binary = os.path.join(
    thispath,
    "../../../",
    # "tests/mod/mod",
    "tests/testpioreg",
)
# binary = "/home/g/riscv/gem5/tests/test_reg_add"
system.workload = SEWorkload.init_compatible(binary)


process = Process()
process.cmd = [binary]
system.cpu.workload = process
system.cpu.createThreads()

root = Root(full_system=False, system=system)
m5.instantiate()

print(f"Beginning simulation!")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
