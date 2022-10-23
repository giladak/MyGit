// dev    : Gilad Kahn
// rev    : Tomer Fridman
// date   : 20.4
// status : approved


#include <iostream> //std
#include <queue>    //queue
#include <thread>   //thread
#include <string>   //string
#include <unistd.h> //sleep

#include "WaitableQueue.hpp"    //waitable queue
#include "TasksClass.hpp"       //Task 
#include "p_queue.hpp"          //PriorityQueue
#include "test.hpp"             //START TEST


using namespace ilrd;


time_t start_time;
time_t end_time;


// template<typename Container>
void PushThreadFunc(WaitableQueue<std::queue<int>> *my_queue)
{  
    for (int i = 0; i < 10; ++i) //when i is size_t it doesnt work, why?
    { 
        my_queue->Push(i);
    }
}

void PushThreadFunc2(WaitableQueue<std::queue<int>> *my_queue)
{  
    sleep(3);

    for (int i = 0; i < 10; ++i) //when i is size_t it doesnt work, why?
    { 
        my_queue->Push(i);
    }
}


void PopThreadFunc(WaitableQueue<std::queue<int>> *my_queue)
{   
    int out = 0;

    for (int i = 0; i < 10; ++i) //when i is size_t it doesnt work, why?
    { 
        my_queue->Pop(out);
    }
} 

void PopThreadFunc2(WaitableQueue<std::queue<int>> *my_queue)
{   
    int out = 0;
    std::chrono::milliseconds time_out(3000);  

    for (int i = 0; i < 10; ++i) //when i is size_t it doesnt work, why?
    { 
        start_time = time(NULL);

        my_queue->Pop(out, time_out);
    }
} 



int main()
{ 
    START_TEST ("Waitable Queue Tests");

    WaitableQueue<std::queue<int>>  my_queue;
    std::string str("hello"); 
    std::thread push_thread;
    std::thread push_with_wait_thread;
    std::thread pop_thread;
    std::thread pop_with_time_thread;

    int out = 0;

    IF("is empty test", true, my_queue.IsEmpty());

    push_thread = std::thread(PushThreadFunc, &my_queue);
    push_thread.join();
    IF("unthread safe push test", false, my_queue.IsEmpty());
    
    pop_thread = std::thread(PopThreadFunc, &my_queue);
    pop_thread.join();
    IF("unthread safe pop test", true, my_queue.IsEmpty());

    
    push_with_wait_thread = std::thread(PushThreadFunc2, &my_queue);

    TIME_MESSURE_START;
    
    my_queue.Pop(out);

    TIME_MESSURE_END;

    IF("pop without time", true, (TIME_MESSURE_ANSWER > 2));

    push_with_wait_thread.join();

   pop_with_time_thread = std::thread(PopThreadFunc2, &my_queue);
   pop_with_time_thread.join();

   end_time = time(NULL);

    IF("pop with time", true, (end_time - start_time >= 3));


    WaitableQueue<PriorityQueue<int>>  p_queue;

    IF("is empty test p_queue", true, p_queue.IsEmpty());

    int value = 5;
    p_queue.Push(value);

    value = 6;
    p_queue.Push(value);

    value = 4;
    p_queue.Push(value);

    IF("test push p_queue", false, p_queue.IsEmpty());

    int out_value = 0;

    p_queue.Pop(out_value);
    IF("test pop p queue", 6, out_value);

    

    END_TEST
}

