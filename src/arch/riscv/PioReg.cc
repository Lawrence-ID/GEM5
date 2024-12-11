#include "arch/riscv/PioReg.hh"
//#include "debug/PioReg.hh"
#include "mem/packet.hh"
#include "mem/packet_access.hh"
#include "sim/system.hh"
#include "enums/ByteOrder.hh"

namespace gem5
{
PioReg::PioReg(const PioRegParams &params)
    : BasicPioDevice(params, sizeof(uint32_t)), regValue(0),byteOrder(params.system->getGuestByteOrder()),pioAddr(params.pio_addr)
{
    // 构造函数中已经通过 BasicPioDevice 设置了 PIO 地址范围和大小?
    //byteOrder = p->byte_order;
    // 设置 PIO 地址范围
    //pioRange = AddrRange(params.pio_addr, params.pio_addr + sizeof(uint32_t) - 1);
}

// 获取设备的地址范围
AddrRangeList
PioReg::getAddrRanges() const
{
    AddrRangeList ranges;
    // ranges.push_back(AddrRange(pioAddr, pioAddr + pioSize - 1));
    ranges.push_back(RangeSize(pioAddr, pioSize));
    return ranges;
}

// // 定义 create() 方法
// PioReg *
// PioRegParams::create() const
// {
//     return new PioReg(this);
// }

Tick
PioReg::read(PacketPtr pkt)
{
    assert(pkt->getSize() == sizeof(uint32_t));

    // 将寄存器值写入到数据包中
    pkt->setUintX(regValue, byteOrder);
    pkt->makeResponse();

    //DPRINTF(PioReg, "Read from register: value=%u\n", regValue);

    // 返回访问延迟
    return pioDelay;
}

Port &
PioReg::getPort(const std::string &if_name, PortID idx)
{
    if (if_name == "pio") {
        return pioPort;
    }
    return BasicPioDevice::getPort(if_name, idx);
}

Tick
PioReg::write(PacketPtr pkt)
{
    assert(pkt->getSize() == sizeof(uint32_t));

    // 从数据包中读取值并存储到寄存器
    regValue = pkt->getUintX(byteOrder);
    pkt->makeResponse();

    //DPRINTF(PioReg, "Write to register: value=%u\n", regValue);

    // 返回访问延迟
    return pioDelay;
}

}