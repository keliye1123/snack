#pragma once

#include<iostream>
#include<thread>
#include <mutex>
#include <queue>
#include <string>
#include <condition_variable>
#include <vector>
#include <functional>

class ThreadPoll {
    //属性
private:
    std::vector<std::thread> threads;       //线程数组
    std::queue<std::function<void()>> tasks;//任务队列

    std::mutex mtx;
    std::condition_variable cv;

    bool stop;  //显示线程池什么时候终止

    //方法
public:
    ThreadPoll(int ThreadNum);

    ~ThreadPoll();

    template<typename T,typename... Args>
   void enqueue(T &&t, Args&&... args) {
        std::function<void()> task = std::bind(std::forward<T>(t),std::forward<Args>(args)...);

        {//限定锁的范围
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }

        cv.notify_one();

    }

};
