#ifndef THREAD_POOL_HH
#define THREAD_POOL_HH

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <atomic> // for std::atomic<bool> if you want to use atomic operations for `should_terminate`

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    void Start();
    void QueueJob(const std::function<void()>& job);
    void Stop();
    bool busy();

private:
    void ThreadLoop();

    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination 
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
    size_t numThreads;
};

#endif