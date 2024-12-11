#ifndef __MY_REGISTER_HH__
#define __MY_REGISTER_HH__

#include "dev/io_device.hh"          // 包含 BasicPioDevice 类
#include "mem/packet.hh" // 定义了Packet类，是gem5中用于表示内存访问请求和响应的基本数据结构。Packet类封装了与内存操作相关的信息(地址、数据、
                         // 命令类型、状态、大小、标记)。主要功能：内存请求、封装数据、处理状态。
#include "mem/packet_access.hh" // 提供了一些与Packet类相关的辅助函数和方法，用于简化对内存访问的操作。它通常包含以下内容：访问函数、类型定义、
                         // 辅助宏和函数。主要功能：简化API、封装复杂性。
#include "params/PioReg.hh"
#include "base/types.hh"
#include "dev/platform.hh"
#include "sim/system.hh"
#include "enums/ByteOrder.hh"
#include "sim/clocked_object.hh" // 包含 ClockedObject 的定义


namespace gem5
{


class PioReg : public BasicPioDevice{
  public:
    //typedef PioRegParams Params; //将PioRegParams类型定义为Params，简化后续代码的书写，使得后面可以通过Params来引用PioRegParams。
    //using Params = PioRegParams;  // 确保 Params 类型定义正确
    PioReg(const PioRegParams &p); // 构造函数，参数是一个指向 Params 类型的指针，通常包含了由 Python 配置文件传入的参数，例如寄存器的地址、大小等。


    // 必须实现的虚函数，包括重写读写方法
    AddrRangeList getAddrRanges() const override;
    Tick read(PacketPtr pkt) override; // 返回一个 Tick 类型的值，表示完成此操作所需的时间周期
    Tick write(PacketPtr pkt) override;

    // 提供端口供系统访问
    Port &getPort(const std::string &if_name, PortID idx = InvalidPortID) override;

  private:
    uint32_t regValue;
    ByteOrder byteOrder; // 用于存储字节序
    Addr pioAddr; // 存储 PIO 地址
};

}

#endif // __MY_REGISTER_HH__