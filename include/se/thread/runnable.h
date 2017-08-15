//
// Created by 欧阳建华 on 2017/8/11.
//

#ifndef SE_RUNNABLE_H
#define SE_RUNNABLE_H


namespace se {
    namespace thread {


        class Runnable {

        public:
            virtual void run() = 0;
        };
    }
}

#endif //SE_RUNNABLE_H
