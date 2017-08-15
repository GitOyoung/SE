//
// Created by 欧阳建华 on 2017/8/14.
//


#include <se/thread/condition.h>
#include <se/thread/mutex.h>

namespace se {
    namespace thread {
        Condition::Condition(Mutex &mutex)
                : mutex(mutex.nativeHandle()) {
            condition = PTHREAD_COND_INITIALIZER;
        }

        void Condition::wait() {
            pthread_cond_wait(&condition, &mutex);
        }

        void Condition::notify() {
            pthread_cond_signal(&condition);
        }

        void Condition::notifyAll() {
            pthread_cond_broadcast(&condition);
        }
    }
}