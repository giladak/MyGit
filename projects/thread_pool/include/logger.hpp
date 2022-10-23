#ifndef __ILRD_RD1167_LOGGER_HPP__
#define __ILRD_RD1167_LOGGER_HPP__

#include <thread>     //thread
#include <fstream>    
#include <iostream>
#include <chrono>     //chrono
#include <ctime>      //ctime 


#include "singleton.hpp"
#include "thread_pool.hpp"



namespace ilrd
{

class WriteTask;

class Logger
{
public:
    enum LogLevel{INFO, ERROR, DEBUG};
    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& other) = delete;
    ~Logger();
    void SetPath(const std::string& path);
    void SetLevel(LogLevel level);
    void Write(const std::string &message, LogLevel level, int line, const std::string& src, std::thread::id thread_id);
    ThreadPool m_thread_pool;

private:
    Logger();
    friend class Singleton<Logger>;
    std::string m_path;
    LogLevel m_level;
    std::ofstream m_file;
};


/* -------------------------------------------------------------------------- */
//!                                write task declaration                     */
/* -------------------------------------------------------------------------- */

class WriteTask : public Task
{
public:
    explicit WriteTask(std::ofstream &file, const std::string &message, Logger::LogLevel level, int line, const std::string& src, std::thread::id thread_id);
private:
    std::ofstream &m_file;
    std::string m_messege;
    Logger::LogLevel m_level;
    int m_line;
    std::string m_src;
    std::thread::id m_thread_id;
    static size_t counter;

    void Execute()
    {
        auto time  = std::chrono::system_clock::now();

        std::time_t actual_time = std::chrono::system_clock::to_time_t(time);

        m_file << "    line:  " << m_line << "   src:   " << m_src << "  thread_id: " << m_thread_id << std::endl;

        m_file << "time: " << ctime(&actual_time) << std::endl;

        m_file << "  message: " << m_messege << "\n\n" << std::endl;
    }
};






}       //ilrd



#endif /* __ILRD_RD1167_LOGGER_HPP__*/




// class WaitEorEnd: public Task
// {
// public:
//     explicit WaitEorEnd(sem_t *sem): Task(LOW), m_sem(sem)
//     {}

// private:
//     sem_t *m_sem;
//     void Execute()
//     {
//         sem_post(m_sem);
//     }
// };

