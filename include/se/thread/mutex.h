//
// Created by 欧阳建华 on 2017/8/14.
//

#ifndef SE_MUTEX_H
#define SE_MUTEX_H

#include <pthread.h>

namespace se {
    namespace thread {
        class Condition;
        class Mutex {
        public:
            typedef pthread_mutex_t native_handle_type;
        public:
            Mutex();
            void lock();
            bool tryLock();
            void unlock();

            native_handle_type nativeHandle() const;
            native_handle_type& nativeHandle();
        private:
            native_handle_type mutex;
        };
    }
}

#endif //SE_MUTEX_H
