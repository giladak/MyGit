#include "logger.hpp"


using namespace ilrd;


/* -------------------------------------------------------------------------- */
//!                              implementations                              */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
//!                           logger implementations                          */
/* -------------------------------------------------------------------------- */

Logger::Logger(): m_thread_pool(1)
{
}

Logger::~Logger()
{
    m_thread_pool.Stop();
    m_file.close();
}

void Logger::SetPath(const std::string& path)
{
    m_path = path;

    m_file.open(m_path, std::ios_base::app);

}

void Logger::SetLevel(LogLevel level)
{
    m_level = level;
}


void Logger::Write(const std::string &message, LogLevel level, int line, const std::string& src, std::thread::id thread_id)
{   
    // auto time = std::chrono::high_resolution_clock::now();
    // auto time_in_nanoseconds =  std::chrono::duration_cast<std::chrono::nanoseconds>(time -5).count();


    if (level <= m_level)
    {
        std::shared_ptr<Task> write_ptr = std::make_shared<WriteTask>(m_file, message, level, line, src, thread_id);
        m_thread_pool.AddTask(write_ptr);
    }
}



/* -------------------------------------------------------------------------- */
//!                           WriteTask implementations                       */
/* -------------------------------------------------------------------------- */

WriteTask::WriteTask(std::ofstream &file, const std::string &message, Logger::LogLevel level, int line, const std::string& src, std::thread::id thread_id): 
Task(static_cast<Priority>(HIGH + 2)),
m_file(file), 
m_messege(message),
m_level(level),
m_line(line),
m_src(src),
m_thread_id(thread_id)
{
}
