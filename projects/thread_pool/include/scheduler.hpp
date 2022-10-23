#ifndef __ILRD_RD1167_SCHEDULER_HPP__
#define __ILRD_RD1167_SCHEDULER_HPP__



#include <iostream>          //boost::asio
#include <boost/asio.hpp>    //boost::asio::steady_timer
#include <thread>            //thread


#include "TasksClass.hpp"    //Task
#include "p_queue.hpp"       //PriorityQueue
#include "WaitableQueue.hpp" //WaitableQueue



namespace ilrd
{

class TimedTask;


/* ------------------ CompareTime task for priority queue ------------------- */
template<typename T> 
class CompareTime
{     
public:
    bool operator()(const T& lhs, const T& rhs ) const;
};


/* -------------------------------- Scheduler ------------------------------- */
class Scheduler
{
public:
    using TimedTasksQueue = WaitableQueue<PriorityQueue<std::shared_ptr<TimedTask>, 
    std::vector<std::shared_ptr<TimedTask>>,CompareTime<std::shared_ptr<TimedTask>>>>;

    Scheduler();
    ~Scheduler();
    Scheduler(const Scheduler &other) = delete;
    Scheduler &operator=(const Scheduler &other) = delete;
    int AddTask(std::shared_ptr<Task> new_task, time_t time_interval);


private:
    boost::asio::steady_timer m_timer;
    int m_flag;
    TimedTasksQueue m_queue;
    std::thread m_thread;
    int Run();
    void Stop();
    void Clear();
};


/* ------------------ TimedTask for priority queue -------------------------- */
class TimedTask
{
public:
    time_t m_time;
private:
    virtual void Execute() = 0;
};


} //ilrd



#endif //SCHEDULER_HPP