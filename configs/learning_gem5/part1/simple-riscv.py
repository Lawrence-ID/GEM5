import m5
from m5.objects import *
import os

system = System()

system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "1GHz"
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = "timing"
system.mem_ranges = [AddrRange("16GB")]
system.cpu = RiscvO3CPU()
# 设置每个 CPU 为 RiscvO3CPU，并创建 4 个核心
# system.cpu = [RiscvO3CPU() for i in range(4)]

system.membus = SystemXBar()
# for cpu in system.cpu:
#     cpu.icache_port = system.membus.cpu_side_ports
#     cpu.dcache_port = system.membus.cpu_side_ports
system.cpu.icache_port = system.membus.cpu_side_ports
system.cpu.dcache_port = system.membus.cpu_side_ports

system.cpu.createInterruptController()

system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports

thispath = os.path.dirname(os.path.realpath(__file__))
binary = os.path.join(
    thispath,
    "../../../",
    # "tests/mod/mod",
    # "tests/test_reg_add", #测试自定义向量指令
    # "tests/fft_test/fft_test", #测试fft算法
    "tests/fft_test/fftarray", #测试fft算法
    # "tests/fft_test/fftcus", #测试fft算法
    # "tests/vfwcmul/vfwcmul", #测试vfwcmuls
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
