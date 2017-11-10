//
// Created by 欧阳建华 on 2017/8/11.
//

#ifndef SE_THREAD_H
#define SE_THREAD_H

#include <se/noncopyable.h>
#include <se/thread/runnable.h>
#include <se/time/duration.h>

#include <pthread.h>

namespace se {
    namespace thread {

        class Thread: public Noncopybale,
                      public Runnable {
        public:
            typedef enum {
                AS_System,
                AS_Process
            }  AttrScope;

            typedef enum   {
                ADS_Detach,
                ADS_Joinable
            } AttrDetachState;

            typedef struct threadId {
                pthread_t pid;
            } Id;

            typedef struct threadAttrs {
                pthread_attr_t pattr;
            } Attrs;

            Thread();

            Thread(Runnable *r);

            ~Thread();

            void start();
            void cancel();
            void join();
            void detach();
            void kill(int signal);
            void setThreadAttrDetachState(AttrDetachState state);
            void setThreadAttrScope(AttrScope scope);

            static void sleep(const se::time::Duration& duration);
            static void exit(void *pdata);
            static Id current();
        protected:
            void run() {}

        private:
            void createThread();

            void initAttr();

        private:
            bool valid;
            Runnable *runnable;
            Id id;
            Attrs attrs;
            static void *threadFunc(void *pdata);

        };

    } // namespace thread end
} //namespace se end




#endif //SE_THREAD_H

