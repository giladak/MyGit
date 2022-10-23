#ifndef __ILRD_RD1167_THREAD_POOL_HPP__
#define __ILRD_RD1167_THREAD_POOL_HPP__

// dev    : Gilad Kahn
// rev    : Sara Shushan
// date   : 14.6.22
// status : approved



#include <iostream>     //shared_ptr
#include <thread>       //thread
#include <exception>    //execution
#include <vector>    //vector


#include "WaitableQueue.hpp" //WaitableQueue
#include "p_queue.hpp"        //PQueue
#include "TasksClass.hpp"    //TasksClass


namespace ilrd
{


/* -------------------------------------------------------------------------- */
//!                            class decleration                              */
/* -------------------------------------------------------------------------- */
template<typename T> 
struct CompareLess
{   
    bool operator()( const T& lhs, const T& rhs ) const
    {   
        return (*lhs < *rhs);
    }
};

class ThreadPool
{
public:
    using TaskQueue = WaitableQueue<PriorityQueue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>,CompareLess<std::shared_ptr<Task>>>>; //CompareLess<std::shared_ptr<Task>>
    explicit ThreadPool(size_t thread_num = std::thread::hardware_concurrency()); // default value may be 1
    ~ThreadPool() noexcept = default;
    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool &operator=(const ThreadPool &other) = delete;

    void AddTask(std::shared_ptr<Task> new_task);
    void AddThread(size_t thread_num = 1);
    void Stop();
    void Pause();
    void Continue();

private:
    int m_thread_num;
    TaskQueue m_queue;
    std::vector<std::thread> m_threads;
    void RunThread();
    void InvokeThread(size_t thread_num);
    std::shared_ptr<std::mutex> m_lock_ptr;
    std::shared_ptr<std::condition_variable_any> m_cv_ptr;
    std::shared_ptr<sem_t> m_semaphore;
};


} // ilrd

#endif //thread pool