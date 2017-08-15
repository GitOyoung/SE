//
// Created by 欧阳建华 on 2017/8/15.
//

#ifndef SE_DISPATCH_QUEUE_H
#define SE_DISPATCH_QUEUE_H

#include <queue>
#include <functional>

#include <se/thread/thread_pool.h>
#include <se/string.h>

namespace se {
    namespace thread {
        typedef std::function<void()> DispatchTask;
        typedef std::queue<DispatchTask> TaskQueue;
        class Thread;
        class Dispatcher;
        class DispatchQueue: public Runnable {
            friend Dispatcher;
        public:
            static DispatchQueue main;
            static DispatchQueue global;
            DispatchQueue(const String& name, bool new_thread = true);
            ~DispatchQueue();

        public:

            virtual void run();

        private:
            void schedule();
            void shutdown();
            void push(const DispatchTask& task);
        private:
            static ThreadPool pool;

            bool  needNewThread;
            bool  running;
            String name;
            TaskQueue taskQueue;
            Thread *pthread;
        };

        class Dispatcher {
        public:
            static void sync(DispatchQueue& queue, const DispatchTask& task);
            static void async(DispatchQueue& queue, const DispatchTask& task);
            static void shutdown(DispatchQueue& queue);
        };
    }
}

#endif //SE_DISPATCH_QUEUE_H
