// concurrent-job-scheduler/src/scheduler.cpp
//
// A minimal concurrent job scheduler with priority support.  Tasks with a lower numerical
// priority value are executed before those with a higher value.  This example uses the C++17
// standard library and is intended for demonstration purposes.

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

struct Task {
    int priority;
    std::function<void()> func;
    bool operator>(const Task &other) const { return priority > other.priority; }
};

class JobScheduler {
public:
    explicit JobScheduler(std::size_t num_threads) : shutdown_(false) {
        for (std::size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this] { this->worker_thread(); });
        }
    }

    ~JobScheduler() { shutdown(); }

    void enqueue_task(Task task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(std::move(task));
        }
        cv_.notify_one();
    }

    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            shutdown_ = true;
        }
        cv_.notify_all();
        for (auto &thread : workers_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

private:
    void worker_thread() {
        while (true) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this] { return shutdown_ || !tasks_.empty(); });
                if (shutdown_ && tasks_.empty()) {
                    return;
                }
                task = std::move(const_cast<Task &>(tasks_.top()));
                tasks_.pop();
            }
            task.func();
        }
    }

    std::vector<std::thread> workers_;
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool shutdown_;
};

int main() {
    // Create a scheduler with 4 worker threads
    JobScheduler scheduler(4);

    // Enqueue some tasks with different priorities
    scheduler.enqueue_task({2, [] { std::cout << "Task with priority 2 executed\n"; }});
    scheduler.enqueue_task({1, [] { std::cout << "Task with priority 1 executed\n"; }});
    scheduler.enqueue_task({3, [] { std::cout << "Task with priority 3 executed\n"; }});

    // Give some time for the tasks to execute
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scheduler.shutdown();
    return 0;
}