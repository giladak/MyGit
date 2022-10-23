// dev    : Gilad Kahn
// rev    : Sara Shushan
// date   : 14.6.22
// status : approved


#include <iostream> //std
#include <queue>    //queue
#include <thread>   //thread
#include <string>   //string
#include <unistd.h> //sleep

#include "WaitableQueue.hpp"    //waitable queue
#include "p_queue.hpp"           //Pqueue
#include "TasksClass.hpp"       //Task 
#include "thread_pool.hpp"      //thread_pool
#include "test.hpp"             //START TEST


using namespace ilrd;


class PrintString: public Task
{

public:
    explicit PrintString(std::string user_string, Priority prior): Task(prior), m_string(user_string)
    {}

private:
    void Execute(){std::cout << "string: " << m_string << std::endl;}


    std::string m_string;
};



size_t AddOne()
{
    static size_t count = 0;
    return (count++);
}

size_t GetNum(size_t a)
{   
    return (a);
}

void TestFunc1();
void TestFunc2();



int main()
{   
    TestFunc1();
    
    sleep(4);
    std::cout << "\n\n\n\n\n\n next test: " << std::endl;

   TestFunc2();
}   





void TestFunc1()
{
    START_TEST ("ThreadPool Tests");

    std::shared_ptr<Task> task1_ptr = std::make_shared<PrintString>("this is task 0", Task::Priority::LOW);
    std::shared_ptr<Task> task2_ptr = std::make_shared<PrintString>("this is task 1", Task::Priority::LOW);
    std::shared_ptr<Task> task3_ptr = std::make_shared<PrintString>("this is task 2", Task::Priority::LOW);
    std::shared_ptr<Task> task4_ptr = std::make_shared<PrintString>("this is task 3", Task::Priority::LOW);

    std::shared_ptr<FutureTask<size_t, size_t>> task5_ptr = std::make_shared<FutureTask<size_t, size_t>>(GetNum, Task::Priority::LOW, 3);

    ThreadPool test_thread_pool(4);

    test_thread_pool.AddTask(task1_ptr);
    test_thread_pool.AddTask(task2_ptr);
    test_thread_pool.AddTask(task3_ptr);
    test_thread_pool.AddTask(task4_ptr);

    test_thread_pool.AddTask(task5_ptr);

    size_t answer = task5_ptr->GetReturnValue();
    
    IF("check future task", 3, answer);

    test_thread_pool.Stop();

    END_TEST
}

void TestFunc2()
{
    START_TEST("test func 2");

    ThreadPool test_thread_pool_2(3);

    std::shared_ptr<FutureTask<size_t>> task6_ptr = std::make_shared<FutureTask<size_t>>(AddOne, Task::Priority::MID);    

    for (int i = 0; i < 5; ++i)
    {
        test_thread_pool_2.AddTask(task6_ptr);
    }

    sleep(3);

    test_thread_pool_2.Pause();

    sleep(1);

    size_t answer = task6_ptr->GetReturnValue();

    IF("check future task test 2", 5, answer);
    
    for (int i = 0; i < 5; ++i)
    {
        test_thread_pool_2.AddTask(task6_ptr);
    }

    answer = task6_ptr->GetReturnValue();

    IF("check pause test", 5, answer);

    test_thread_pool_2.Continue();

    sleep(5);

    answer = task6_ptr->GetReturnValue();

    IF("check continue test", 10, answer);


    // test_thread_pool_2.Pause();
    // test_thread_pool_2.Continue();

    test_thread_pool_2.Stop();

    END_TEST
}

