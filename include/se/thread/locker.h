//
// Created by 欧阳建华 on 2017/8/14.
//

#ifndef SE_LOCKER_H
#define SE_LOCKER_H

namespace se {
    namespace thread {
        class Mutex;
        class Locker {
        public:
            Locker(Mutex &mutex);
            ~Locker();
        private:
            Mutex& mutex;
        };
    }
}

#endif //SE_LOCKER_H
