#ifndef _BPOOL_H__
#define _BPOOL_H__

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






#endif
