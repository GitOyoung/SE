//
// Created by 欧阳建华 on 2017/8/11.
//


#include <se/thread/thread_pool.h>
#include <se/thread/locker.h>

namespace se {
    namespace thread {
        ThreadPool::ThreadPool(int max_thread_count)
                : running(false)
                , maxThreadCount(max_thread_count)
                , freeThreadCount(0)
                , currentThreadCount(0)
                , mutex()
                , notEmpty(mutex) {

        }

        void ThreadPool::run() {
            while(running) {
                Locker locker(mutex);
                ++freeThreadCount;
                while(running && taskList.empty()) notEmpty.wait();;
                --freeThreadCount;
                if(running) {
                    auto &task = taskList.front();
                    taskList.pop();
                    if (task) {
                        task();
                    }
                }
            }

        }

        void ThreadPool::push(const Task task) {

            Locker locker(mutex);
            taskList.push(task);
            if(freeThreadCount == 0 && currentThreadCount < maxThreadCount) {
                createNewWorkThread();
            }
            notEmpty.notifyAll();
        }

        void ThreadPool::createNewWorkThread() {
            auto thread = new Thread(this);
            threadList.push_back(thread);
            currentThreadCount = threadList.size();
            if(!running) running = true;
        }

        void ThreadPool::shutdown() {
            running = false;
            notEmpty.notifyAll();
        }

        ThreadPool::~ThreadPool() {
            shutdown();
            for(auto &thread: threadList) {
                thread->join();
                delete thread;
            }
        }
    }
}
