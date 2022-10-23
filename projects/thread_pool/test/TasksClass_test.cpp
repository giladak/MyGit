// dev    : Gilad Kahn
// rev    : 
// date   : 
// status : approved


#include <iostream> //std
#include <queue>    //queue
#include <thread>   //thread
#include <string>   //string
#include <unistd.h> //sleep

#include "WaitableQueue.hpp"    //waitable queue
#include "p_queue.hpp"           //Pqueue
#include "TasksClass.hpp"       //Task 
#include "test.hpp"             //START TEST


using namespace ilrd;

class PrintString: public Task
{

public:
    explicit PrintString(std::string user_string, Priority prior): Task(prior), m_string(user_string)
    {}

    void Execute(){std::cout << "string: " << m_string << std::endl;}


    std::string m_string;
};


size_t GetTwo(size_t a)
{   
    sleep(2);

    return (a);
}





int main()
{ 
    START_TEST ("Waitable Queue Tests");

    PrintString hello("hello world", Task::Priority::MID);
    IF("simple task test","hello world", hello.m_string);
    hello.Execute();

    
    FutureTask<size_t, size_t> future(GetTwo, Task::Priority::LOW, 5);
    
    IF("future task test", 5, future.GetReturnValue());

    END_TEST
}

