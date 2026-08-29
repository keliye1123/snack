#include "poll.h"



// int main() {
//     ThreadPoll pool(4);
//     for (int i=0; i<10; i++) {
//         pool.enqueue([i] {
//             printf("task:%d IS RUN\n",i);
//             printf("task:%d IS SLEEP\n",i);
//         });
//     }
// }

ThreadPoll::ThreadPoll(int ThreadNum) {
    stop = false;
    for (int i=0; i<ThreadNum; i++) {
        threads.emplace_back([this] {
            while (true) {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] {
                    return !tasks.empty() || stop;
                });

                if (stop && tasks.empty()) return;

                std::function<void()> task(std::move(tasks.front()));
                tasks.pop();
                lock.unlock();
                task();
                //unlcok放在task的前和后都不会抢占tasks工作队列，但放在task前会导致线程抢占io资源

            }
        } );
    }
};

ThreadPoll::~ThreadPoll() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }

    cv.notify_all();
    for (auto& t : threads) {
        t.join();
    }
}

