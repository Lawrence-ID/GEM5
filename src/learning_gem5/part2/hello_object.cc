/*
 * Copyright (c) 2017 Jason Lowe-Power
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "learning_gem5/part2/hello_object.hh"

#include "base/logging.hh"
#include "base/trace.hh"//添加debug调试头后需要添加的
#include "debug/HelloExample.hh"//添加debug调试头后需要添加的

namespace gem5
{

HelloObject::HelloObject(const HelloObjectParams &params) :
    SimObject(params),
    // This is a C++ lambda. When the event is triggered, it will call the
    // processEvent() function. (this must be captured)
    event([this]{ processEvent(); }, name() + ".event"),
    goodbye(params.goodbye_object),
    // Note: This is not needed as you can *always* reference this->name()
    myName(params.name),//将参数对象中的名称存储在成员变量myName中，以便稍后使用
    latency(params.time_to_wait),
    timesLeft(params.number_of_fires)
{
    DPRINTF(HelloExample, "Created the hello object\n");//用调试语句替换std::cout调用
    panic_if(!goodbye, "HelloObject must have a non-null GoodbyeObject");//条件检查
    //用于条件检查的宏或函数，通常用于在调试或开发过程中捕获错误。它的作用是如果condition为真，
    //则触发一个错误，通常会中止程序并输出message。
}

void
HelloObject::startup()
{
    // Before simulation starts, we need to schedule the event
    schedule(event, latency);
}

void
HelloObject::processEvent()
{
    timesLeft--;
    DPRINTF(HelloExample, "Hello world! Processing the event! %d left\n",
                          timesLeft);

    if (timesLeft <= 0) {
        DPRINTF(HelloExample, "Done firing!\n");
        goodbye->sayGoodbye(myName);
    } else {
        schedule(event, curTick() + latency);
    }
}

} // namespace gem5
