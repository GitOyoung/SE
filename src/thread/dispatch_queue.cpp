//
// Created by 欧阳建华 on 2017/8/15.
//

#include <se/thread/dispatch_queue.h>
#include <se/thread/locker.h>

#include <stdio.h>

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
            dispatch();
        }

        void DispatchQueue::dispatch() {
            while(running) {
                schedule();
            }
        }

        void DispatchQueue::scheduleAll() {
            while(!taskQueue.empty()) {
                schedule();
            }
        }

        void DispatchQueue::shutdown() {
            running = false;
        }

        void DispatchQueue::schedule() {
            if(!taskQueue.empty()) {
                printf("schedule task\n");
                if(pthread) {
                    pool.push(taskQueue.front());
                    taskQueue.pop();
                } else {
                    taskQueue.front()();
                    taskQueue.pop();
                }
            }

        }

        void DispatchQueue::push(const DispatchTask &task) {
            if(task) {
                printf("push task\n");
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