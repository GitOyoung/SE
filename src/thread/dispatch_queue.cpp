//
// Created by 欧阳建华 on 2017/8/15.
//

#include <se/thread/dispatch_queue.h>
#include <se/thread/thread.h>
#include <se/thread/mutex.h>
#include <se/thread/locker.h>
#include <se/thread/condition.h>

namespace se {
    namespace thread {

        DispatchQueue DispatchQueue::main("main", false);
        DispatchQueue DispatchQueue::global("global");

        ThreadPool DispatchQueue::pool;

        DispatchQueue::DispatchQueue(const String& name, bool new_thread)
                : name(name)
                , running(false)
                , needNewThread(new_thread) {

        }

        void DispatchQueue::run() {
            running = true;
            while (running) {
                schedule();
            }
        }

        void DispatchQueue::shutdown() {
            running = false;
        }

        void DispatchQueue::schedule() {
            if(!taskQueue.empty()) {
                if(pthread) {
                    pool.push(taskQueue.front());
                    taskQueue.pop();
                } else {
                    taskQueue.front()();
                }
            }

        }

        void DispatchQueue::push(const DispatchTask &task) {
            if(task) {
                taskQueue.push(task);
            }
            if(pthread == nullptr && needNewThread) {
                pthread = new Thread(this);
            }
        }

        DispatchQueue::~DispatchQueue() {
            shutdown();
            if(pthread) {
                delete pthread;
            }
        }

        void Dispatcher::async(DispatchQueue &queue, const DispatchTask &task) {
            queue.push(task);
        }

        void Dispatcher::sync(DispatchQueue &queue, const DispatchTask &task) {
            Mutex mutex;
            Condition finish(mutex);

            queue.push([task, &finish](){
                task();
                finish.notify();
            });
            finish.wait();
        }


        void Dispatcher::shutdown(DispatchQueue &queue) {
            queue.shutdown();
        }
    }
}