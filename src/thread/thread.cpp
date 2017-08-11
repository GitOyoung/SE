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

    }
}