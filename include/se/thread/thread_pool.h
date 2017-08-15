//
// Created by 欧阳建华 on 2017/8/11.
//

#ifndef SE_THREAD_POOL_H
#define SE_THREAD_POOL_H

#include <se/thread/thread.h>
#include <se/thread/mutex.h>
#include <se/thread/condition.h>

#include <vector>
#include <queue>
#include <functional>

namespace se {
    namespace thread {

    typedef std::function<void()> Task;

    class ThreadPool: public Runnable
    {

    public:
        explicit ThreadPool(int max_thread_count = 4);

        void push(const Task task);
        void shutdown();

        ~ThreadPool();
    protected:
        virtual void run();

    private:
        void createNewWorkThread();

    private:
        bool running;
        int maxThreadCount;
        int freeThreadCount;
        int currentThreadCount;
        std::vector<Thread *> threadList;
        std::queue<Task> taskList;

        Mutex mutex;
        Condition notEmpty;
    };


    }
}

#endif //SE_THREAD_POOL_H
