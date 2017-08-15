//
// Created by 欧阳建华 on 2017/8/14.
//

#include <se/thread/locker.h>
#include <se/thread/mutex.h>

namespace se {
    namespace thread {
        Locker::Locker(Mutex &mutex): mutex(mutex) {
            this->mutex.lock();
        }

        Locker::~Locker() {
            mutex.unlock();
        }
    }
}