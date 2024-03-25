#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    // Constructor
    ThreadPool(size_t);
    
    // Function to enqueue tasks
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    
    // Destructor
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;
    
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
 
// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
    :   stop(false)
{
    for(size_t i = 0;i<threads;++i)
        // Create worker threads
        workers.emplace_back(
            [this]
            {
                for(;;)
                {
                    std::function<void()> task;

                    {
                        // Lock the queue mutex
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // Wait until there is a task or stop is requested
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->tasks.empty(); });
                        // If the thread should stop and no more tasks, return
                        if(this->stop && this->tasks.empty())
                            return;
                        // Get the next task
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    // Execute the task
                    task();
                }
            }
        );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    // Create a packaged task for the function and its arguments
    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
    // Get a future for the result
    std::future<return_type> res = task->get_future();
    {
        // Lock the queue mutex
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        // Add the task to the queue
        tasks.emplace([task](){ (*task)(); });
    }
    // Notify one waiting thread that a task is available
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        // Lock the queue mutex
        std::unique_lock<std::mutex> lock(queue_mutex);
        // Set stop flag to true
        stop = true;
    }
    // Notify all waiting threads that the pool is stopping
    condition.notify_all();
    // Join all worker threads
    for(std::thread &worker: workers)
        worker.join();
}

#endif
