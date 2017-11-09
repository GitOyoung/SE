//
// Created by 欧阳建华 on 2017/8/11.
//

#include <se/thread/thread.h>


namespace se {
    namespace thread {

        struct threadId {
            pthread_t pid;
        };

        Thread::Thread()
        : valid(false)
        , runnable(this) {
            initAttr();
        }
        Thread::Thread(Runnable *r)
        : valid(false)
        , runnable(r) {
            initAttr();
        }

        Thread::~Thread() {
            pthread_attr_destroy(&attrs.pattr);
            pthread_cancel(id.pid);
        }



        void Thread::start()  {
            createThread();
        }

        void Thread::kill(int signal) {
            pthread_kill(id.pid, signal);
        }

        void Thread::cancel() {
            pthread_cancel(id.pid);
        }

        void Thread::join()  {
            pthread_join(id.pid, nullptr);
        }

        void Thread::detach() {
            pthread_detach(id.pid);
        }

        void Thread::sleep(const se::time::Duration &duration)  {
            struct timespec interval = duration.interval();
            nanosleep(&interval, nullptr);
        }

        void Thread::createThread()  {
            valid = pthread_create(&id.pid, &attrs.pattr, threadFunc, runnable) == 0;
        }

        void Thread::initAttr()  {
            pthread_attr_init(&attrs.pattr);
        }



        void * Thread::threadFunc(void *pdata) {
            Runnable *runnable = static_cast<Runnable *>(pdata);
            if(runnable) {
                runnable->run();
            }
            return runnable;
        }

        void Thread::setThreadAttrDetachState(AttrDetachState state)
        {
            pthread_attr_setdetachstate(&attrs.pattr,
                                        state == ADS_Joinable ? PTHREAD_CREATE_JOINABLE
                                                              : PTHREAD_CREATE_DETACHED);
        }

        void Thread::setThreadAttrScope(AttrScope scope) {
            pthread_attr_setscope(&attrs.pattr,
                                  scope == AS_System ? PTHREAD_SCOPE_SYSTEM
                                                     : PTHREAD_SCOPE_PROCESS);
        }

        void Thread::exit(void *pdata) {
            pthread_exit(pdata);
        }

        Thread::Id Thread::current() {
            Id pid = { pthread_self()};
            return pid;
        }
    }
}