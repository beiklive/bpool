#pragma once
#include <thread>
#include <mutex>
#include <vector>       
#include <queue>
#include <functional>
#include <condition_variable>
class bpool
{
private:
    /* data */
    std::vector<std::thread> threads; // 储存线程池中的线程
    std::queue<std::function<void()>> tasks; // 储存任务队列
    std::mutex tasks_mtx;
    std::condition_variable cv;
    bool stop;

public:
    bpool(int num_threads);
    ~bpool();

    void add_task(std::function<void()> task);
};


bpool::bpool(int num_threads) : stop(false)
{
    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back([this](){
            while(true){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(tasks_mtx);
                    cv.wait(lock, [this](){
                        return stop || !tasks.empty();
                    });
                    if(stop && tasks.empty()) return;
                    task = tasks.front();
                    tasks.pop();
                }
                task();
            }
        });
    }
}
void bpool::add_task(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        if (stop)
        {
            throw std::runtime_error("bpool is stopped");
        }
        
        tasks.emplace(task);
    }
    cv.notify_one();
}

bpool::~bpool()
{
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        stop = true;
    }
    cv.notify_all();  // 唤醒所有等待的线程
    for(auto &t : threads)  // 结束所有线程
        if (t.joinable())
        {
            t.join();
        }
}

