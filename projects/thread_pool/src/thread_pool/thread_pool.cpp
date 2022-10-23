#include "thread_pool.hpp"


using namespace ilrd;


/* -------------------------------------------------------------------------- */
//!                               implementations                             */
/* -------------------------------------------------------------------------- */


/* ---------------------------------- ctor ---------------------------------- */
ThreadPool::ThreadPool(size_t thread_num): 
m_thread_num(thread_num), 
m_lock_ptr(std::make_shared<std::mutex>()),
m_cv_ptr(std::make_shared<std::condition_variable_any>()), 
m_semaphore(std::make_shared<sem_t>())
{
    InvokeThread(m_thread_num);
}



/* ------------------------------ invoke thread ----------------------------- */

void ThreadPool::InvokeThread(size_t thread_num)
{   
    for (size_t i = 0; i < thread_num; ++i)
    {
        m_threads.push_back(std::thread([&](){RunThread();}));
    } 
}



/* ----------------------------------- Add Task ----------------------------- */
void ThreadPool::AddTask(std::shared_ptr<Task> new_task)
{
    m_queue.Push(new_task);
}



/* -------------------------------- Add Thread ------------------------------ */
void ThreadPool::AddThread(size_t thread_num)
{   
    m_thread_num += thread_num;
    InvokeThread(thread_num);
}



/* -------------------------------- RunThread ------------------------------- */
void ThreadPool::RunThread()
{   
    std::shared_ptr<Task> execution_task;

    try
    {
        while(1)
        {
            m_queue.Pop(execution_task);

            execution_task->Execute();
        }
    }

    catch(const MyException & my_exeption)
    {}
    
}


/* ---------------------------------- Stop ---------------------------------- */
void ThreadPool::Stop()
{   
    std::shared_ptr<Task> bad_apple_ptr = std::make_shared<BadApple>();
    
    for (int i = 0; i < m_thread_num; i++)
    {  
        AddTask(bad_apple_ptr);
    }

    for (int i = 0; i < m_thread_num; i++)
    {  
        m_threads[i].join();
    }
}   


/* ---------------------------------- Pause --------------------------------- */
void ThreadPool::Pause()
{   
    std::shared_ptr<Task> Pause_task_ptr = std::make_shared<PauseTask>(m_cv_ptr,m_semaphore ,m_lock_ptr);
    
    for (int i = 0; i < m_thread_num; i++)
    {  
        AddTask(Pause_task_ptr);
    }
}

/* ---------------------------------- Continue ------------------------------ */
void ThreadPool::Continue()
{
    //m_cv_ptr->notify_all();

    for (int i = 0; i < m_thread_num; ++i)
    {
        sem_post(m_semaphore.get());
    }
}


