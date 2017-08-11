//
// Created by 欧阳建华 on 2017/4/25.
//


#include <iostream>
#include <se/thread/thread.h>

class Test: public se::thread::Runnable
{
public:
    virtual void run() {
        std::cout<< "子线程"<< std::endl;
    }
};

int main(int argc, char **argv)
{

    Test test;

    se::thread::Thread thread(&test);

    thread.join();

    return 0;
}