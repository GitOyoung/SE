//
// Created by 欧阳建华 on 2017/8/11.
//

#ifndef SE_THREAD_H
#define SE_THREAD_H

#include <se/thread/runnable.h>
#include <thread>

namespace se {
    namespace thread {


        typedef std::thread::id ThreadId;

        class current {
        public:
            static ThreadId threadId();
            static void sleep(int seconds, int miliseconds = 0, int microseconds = 0);
        };


        class Thread: public Runnable
        {
        public:
            explicit Thread(Runnable * func = nullptr);
            void join();
            bool joinable() const;
            void detach();
            ThreadId getId() const;

            ~Thread();
        protected:
            virtual void run();
        private:
            Runnable *runnable;
            std::thread thread;
        };

    } // namespace thread end
} //namespace se end




#endif //SE_THREAD_H

