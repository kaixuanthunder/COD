#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

int main()
{
    // Create a thread pool with 4 threads
    ThreadPool pool(4);
    // Vector to store futures of results
    std::vector< std::future<int> > results;

    // Enqueue tasks to the thread pool
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            // Enqueue a lambda function with index i
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                // Simulate work by sleeping for 1 second
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                // Return the square of the index
                return i*i;
            })
        );
    }

    // Wait for all tasks to finish and print results
    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}
