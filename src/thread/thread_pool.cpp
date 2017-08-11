//
// Created by 欧阳建华 on 2017/8/11.
//


#include <se/thread/thread_pool.h>


namespace se {
    namespace thread {
        ThreadPool::ThreadPool(int max_thread_count)
                : maxThreadCount(max_thread_count)
                , freeThreadCount(0)
                , currentThreadCount(0) {

        }

        void ThreadPool::run() {

            while(active) {
                ++freeThreadCount;
                // wait();
                --freeThreadCount;
                if(taskList.empty()) continue;

                auto &task = taskList.front();
                if(task) task();
            }

        }

        void ThreadPool::push(const Task task) {
            taskList.push_back(task);
            if(freeThreadCount == 0 && currentThreadCount < maxThreadCount) {
                createNewWorkThread();
            }
            //notify()
        }

        void ThreadPool::createNewWorkThread() {
            auto thread = new Thread(this);
            threadList.push_back(thread);
            currentThreadCount = threadList.size();
        }

        ThreadPool::~ThreadPool() {
            for(auto &thread: threadList) {
                delete thread;
            }
        }
    }
}
