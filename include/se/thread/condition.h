//
// Created by 欧阳建华 on 2017/8/14.
//

#ifndef SE_CONDITION_H
#define SE_CONDITION_H

#include <pthread.h>

namespace se {
    namespace thread {
        class Mutex;
        class Condition {
        public:
            Condition(Mutex& mutex);

            void wait();
            template <class Predicate>
            void wait(Predicate predicate);

            void notify();
            void notifyAll();

        private:
            pthread_mutex_t& mutex;
            pthread_cond_t condition;
        };

        template <class Predicate>
        void Condition::wait(Predicate predicate) {
            while(!predicate()) wait();
        }
    }
}

#endif //SE_CONDITION_H
