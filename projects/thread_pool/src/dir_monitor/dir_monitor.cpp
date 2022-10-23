#include "dir_monitor.hpp"

using namespace ilrd;



/* -------------------------------------------------------------------------- */
//!                              implementations                              */
/* -------------------------------------------------------------------------- */


/* ---------------------------------- ctor ---------------------------------- */

DirMonitor::DirMonitor(const std::string &path): 
m_inotify_fd(inotify_init()),
m_log(&Singleton<Logger>::GetInstance()), 
m_is_running(true),
m_thread(&DirMonitor::ListenThread, this) //[this]{this->ListenThread();}
{
    std::string logger_path(path);

    while('/' != *(logger_path.end() - 1)) //check if neccessary
    {
        logger_path.pop_back();
    }
    logger_path.pop_back();

    logger_path += "/logger.txt";

    m_log->SetPath(logger_path);
    m_log->SetLevel(Logger::LogLevel::DEBUG);


    if (-1 == this->m_inotify_fd)
    {
        this->m_log->Write("Unable to start monitoring", Logger::LogLevel::ERROR,
                               __LINE__, __FILE__,  std::this_thread::get_id());

        throw std::runtime_error("Unable to start monitoring");
    }

    this->m_log->Write("starting monitoring", Logger::LogLevel::ERROR,
                               __LINE__, __FILE__,  std::this_thread::get_id());

    if(-1 == inotify_add_watch(m_inotify_fd, path.c_str(), 
                                                         IN_CREATE | IN_MODIFY))
    {   
        std::string error_messege("unable to open path: ");

        error_messege += strerror(errno);

        m_log->Write(error_messege, Logger::LogLevel::ERROR, __LINE__, __FILE__, 
                                                    std::this_thread::get_id());
    }    
}


/* ----------------------------- Get Dispatcher ----------------------------- */

Dispatcher<std::string> *DirMonitor::GetDispatcher()
{
    return &m_dispatcher;
}

/* ----------------------------- thread function ---------------------------- */
void DirMonitor::ListenThread()
{   
    const size_t max_buffer = 1024;
    char buffer[max_buffer] = {0};
    Logger *thread_logger = &Singleton<Logger>::GetInstance();

    thread_logger->Write("started monitoring", Logger::LogLevel::ERROR,
                                __LINE__, __FILE__,  std::this_thread::get_id());

    struct timeval       timeout;
    struct inotify_event event;

    int ret =            0;
    fd_set               descriptor_set;
    FD_ZERO(&descriptor_set);



    while(m_is_running)
    {
        timeout.tv_sec  = 10;
        timeout.tv_usec = 0;
        FD_SET(m_inotify_fd, &descriptor_set);
        
        ret = select(m_inotify_fd + 1, &descriptor_set, NULL, NULL, &timeout);

        if (0 >= ret)
        {
            if (-1 == ret)
            {
                perror("ret");
            }
        }

        if (1 == FD_ISSET(m_inotify_fd, &descriptor_set))
        {   
            if (0 >= read(this->m_inotify_fd, &event, max_buffer))
            {   
                std::string error_messege("Unable to read: ");

                error_messege += strerror(errno);

                thread_logger->Write(error_messege, Logger::LogLevel::INFO, __LINE__, 
                                         __FILE__,  std::this_thread::get_id());

                break; 
            }
            
            strcpy(buffer, event.name);
            m_dispatcher.NotifyAll(event.name);

            printf("event name: %s\n", event.name);
        }
    }


    thread_logger->Write("finished monitoring", Logger::LogLevel::ERROR,
                                __LINE__, __FILE__,  std::this_thread::get_id());
}


/* ---------------------------------- dtor ---------------------------------- */

DirMonitor::~DirMonitor()
{
    close(m_inotify_fd);
    m_is_running = false;
    m_thread.join();
} 


