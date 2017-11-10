//
// Created by 欧阳建华 on 2017/4/25.
//


#include <se/thread/thread.h>

#include <iostream>

class TestThread: public se::thread::Thread {
public:
    void run() {
        int time = 10;
        while(time --> 0) {
            std::cout << "TestThread is running: "
                      << time << " left\n";
            sleep(se::time::Seconds(1));
        }
    }
};


int main(int argc, char **argv)
{

    TestThread thread;


    thread.setThreadAttrDetachState(se::thread::Thread::ADS_Joinable);
    thread.start();

    thread.join();
    return 0;
}