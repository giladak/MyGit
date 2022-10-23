
#include <memory>
#include <thread>


#include "logger.hpp"
#include "TasksClass.hpp"
#include "test.hpp"

using namespace ilrd;

int main()
{
    Logger *MyLogger = &Singleton<Logger>::GetInstance();
    MyLogger->SetLevel(Logger::LogLevel::INFO);
    MyLogger->SetPath("/home/shikamaru/Desktop/git/gilad-kahn/projects/final_project/framework/test/logger.txt");
    std::string check("check num : ");


    for (size_t i = 0; i < 5; ++i)
    {       
        check.insert(check.end(), i + '0');

        MyLogger->Write(check, Logger::LogLevel::INFO, __LINE__, __FILE__, std::this_thread::get_id());

        check.erase(check.length() - 1, check.length());
    }


    return 0;


}