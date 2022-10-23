#include "TasksClass.hpp"

using namespace ilrd;

/* -------------------------------------------------------------------------- */
//!                        Task implementations                               */
/* -------------------------------------------------------------------------- */


/* -------------------------------- task ctor ------------------------------- */
Task::Task(Priority priority): m_priority(priority)
{}


/* ------------------------------task operator  < ----------------------------*/
bool Task::operator<(const Task& other)
{
    return(m_priority < other.m_priority);
}


/* ------------------------------task operator  <= ---------------------------*/
bool Task::operator<=(const Task& other)
{
    return(m_priority <= other.m_priority);
}



/* -------------------------------------------------------------------------- */
//!                    BadApple implementations                               */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- ctor ---------------------------------- */
BadApple::BadApple(): Task(STOP_TASK)
{}   


/* ------------------------------- execute ---------------------------------- */
void BadApple::Execute()
{
        throw MyException();
} 




/* -------------------------------------------------------------------------- */
//!                   PauseTask implementations                               */
/* -------------------------------------------------------------------------- */

/* -------------------------------- PauseTask ------------------------------- */
PauseTask::PauseTask(std::shared_ptr<std::condition_variable_any> cv, std::shared_ptr<sem_t> sem , std::shared_ptr<std::mutex> lock): 
                                    Task(STOP_TASK), m_cv(cv), m_sem(sem), m_lock(lock) 
{
}   

/* --------------------------------- Execute -------------------------------- */

void PauseTask::Execute()
{   
    std::unique_lock<std::mutex> scope_lock(*m_lock);

    //m_cv->wait(*m_lock);

    sem_wait(m_sem.get());
}   
