//
// Created by 欧阳建华 on 2017/8/14.
//

#include <se/thread/mutex.h>

namespace se {
    namespace thread {
        Mutex::Mutex(): mutex() {
            mutex = PTHREAD_MUTEX_INITIALIZER;
        }

        void Mutex::lock() {
            pthread_mutex_lock(&mutex);
        }

        bool Mutex::tryLock() {
            return pthread_mutex_trylock(&mutex);
        }

        void Mutex::unlock() {
            pthread_mutex_unlock(&mutex);
        }


        Mutex::native_handle_type Mutex::nativeHandle() const {
            return mutex;
        }

        Mutex::native_handle_type& Mutex::nativeHandle() {
            return mutex;
        }
    }
}