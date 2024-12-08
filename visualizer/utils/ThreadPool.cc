#include "ThreadPool.hh"

ThreadPool::ThreadPool(size_t numThreads): numThreads(numThreads)
{
    Start();
}

ThreadPool::~ThreadPool()
{
    Stop();
}

void ThreadPool::Start()
{
    for (size_t i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(&ThreadPool::ThreadLoop, this);
    }
}

void ThreadPool::QueueJob(const std::function<void()> &job)
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        jobs.push(job);
    }
    mutex_condition.notify_one();
}

void ThreadPool::Stop()
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();

    for (std::thread &thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    threads.clear();
}

bool ThreadPool::busy()
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    return !jobs.empty();
}

void ThreadPool::ThreadLoop()
{
    while (true)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mutex_condition.wait(lock, [this]
                                 { return !jobs.empty() || should_terminate; });
            if (should_terminate && jobs.empty())
            {
                return;
            }
            job = std::move(jobs.front());
            jobs.pop();
        }
        job();
    }
}
