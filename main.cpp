//
// Created by 欧阳建华 on 2017/4/25.
//


#include <stdio.h>
#include <se/thread/dispatch_queue.h>





int main(int argc, char **argv)
{

    auto &mainQueue = se::thread::DispatchQueue::main;
    auto &globalQueue = se::thread::DispatchQueue::global;

    using se::thread::Dispatcher;

    Dispatcher::async(globalQueue, [&]() {
        Dispatcher::async(mainQueue, [&](){
            printf("run in main0 thread: %ld\n", se::thread::current::threadId());
            Dispatcher::shutdown(mainQueue);
        });
        printf("run in other thread: %ld\n", se::thread::current::threadId());
    });

    printf("run in main thread: %ld\n", se::thread::current::threadId());
    mainQueue.run();

    return 0;
}