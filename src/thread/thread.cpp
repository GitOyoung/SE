//
// Created by 欧阳建华 on 2017/8/11.
//

#include <se/thread/thread.h>



namespace se {
    namespace thread {



        Thread::Thread(Runnable *func)
                : runnable((Runnable *) (func ? func : this))
        , thread(&Runnable::run, runnable) {

        }

        void Thread::run() {

        }

        void Thread::join() {
            thread.join();
        }

        bool Thread::joinable() const {
            return thread.joinable();
        }

        void Thread::detach() {
            thread.detach();
        }

        ThreadId Thread::getId() const {
            return (ThreadId)thread.get_id();
        }

        Thread::~Thread() {
            if(joinable()) {
                join();
            }
        }


        ThreadId current::threadId() {
            return std::this_thread::get_id();
        }

        void current::sleep(int seconds, int milliseconds, int microseconds) {
            if(seconds > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(seconds));
            }

            if(milliseconds > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
            }

            if(microseconds > 0) {
                std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
            }
        }


    }
}