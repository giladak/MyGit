// dev    : Gilad Kahn
// rev    : Sara Shushan
// date   : 14.6.22
// status : approved



#ifndef __ILRD_RD1167_TASK_HPP__
#define __ILRD_RD1167_TASK_HPP__


#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <mutex>              // for mutex
#include <condition_variable> // for condition variable




namespace ilrd
{

class ThreadPool;

 /* ------------------------------------------------------------------------- */
 //!                           class Task decleration                         */
 /* ------------------------------------------------------------------------- */

class Task
{
public:
    enum Priority {LOW = 0, MID, HIGH, STOP_TASK}; //change stop task
    Task(Priority priority = MID);
    virtual ~Task() = default;
    Task(const Task& other) = delete;
    Task& operator=(const Task& other) = delete;
    bool operator<(const Task& other);
    bool operator<=(const Task& other);

private:
    virtual void Execute() = 0;  // virtual void operator()() = 0; 
    Priority m_priority;

    friend ThreadPool;  
};

/* -------------------------------------------------------------------------- */
//!                          future task decleration                          */
/* -------------------------------------------------------------------------- */
template<typename T, typename ...Args>
class FutureTask: public Task
{
public:
    using func_t = std::function<T (Args...)>;
    explicit FutureTask(func_t func_ptr, Priority priority, Args ...params);
    ~FutureTask() = default;
    FutureTask(const FutureTask& other) = delete;
    FutureTask& operator=(const FutureTask& other) = delete;
    T GetReturnValue();

private:
    std::function<T()> m_ptr;
    T m_ret;
    boost::interprocess::interprocess_semaphore  m_sem;
    void Execute();  // void operator()();
};




/* -------------------------------------------------------------------------- */
//!                          FutureTask Ctor Implementation                   */
/* -------------------------------------------------------------------------- */
/* ----------------------------- FutureTask Ctor ---------------------------- */
template<typename T, typename ...Args>
FutureTask<T, Args...>::FutureTask(func_t func_ptr, Priority priority, Args ...params):
    Task(priority),
    m_ptr([=](){return func_ptr(params...);}), 
    m_sem(0)
{
    Execute();
}


/* ----------------------------- FutureTask Execute---------------------------*/
template<typename T, typename ...Args>
void FutureTask<T, Args...>::Execute()
{
    m_ret = m_ptr();
    m_sem.post();
}


/*------------------------ FutureTask GetReturnValue -------------------------*/
template<typename T, typename ...Args>
T FutureTask<T, Args...>::GetReturnValue()
{   
    m_sem.wait();
    return (m_ret);
}


/* -------------------------------------------------------------------------- */
//!           bad apple class decleration                                     */
/* -------------------------------------------------------------------------- */

class MyException : public std::exception
{};


class BadApple: public Task
{
public:
    BadApple();
    ~BadApple() = default;
    BadApple(const BadApple & other_) = delete;
    BadApple& operator=(const BadApple & other_) = delete;

private:
    void Execute();
};

/* -------------------------------------------------------------------------- */
//!               pause class decleartion and                                 */
/* -------------------------------------------------------------------------- */
class PauseTask: public Task
{
public:
    PauseTask(std::shared_ptr<std::condition_variable_any> cv, std::shared_ptr<sem_t> sem ,std::shared_ptr<std::mutex> lock);
    ~PauseTask() = default;
    PauseTask(const PauseTask & other_) = delete;
    PauseTask& operator=(const PauseTask & other_) = delete;

private:
    std::shared_ptr <std::condition_variable_any> m_cv;
    std::shared_ptr <sem_t> m_sem;
    std::shared_ptr <std::mutex> m_lock;
    
    void Execute();   
};






}   //ilrd

#endif  //tasks class