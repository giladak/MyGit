


C++ Thread pool:

- In this project you can find a fully c++17 synchronous thread pool.

- To add Tasks to the thread pool, The user needs to inherit the abstract class "Task"
that appears in the "TasksClass.hpp" file in implement the pure virtual function "execute". The thread pool will push the task to a synchronous Waitable Queue and execute it according to the tasks priority.

- To recieve a return value from a task, the user should inherit "FutureTask" instead of "Task". 

for further instructions and details, see the relevant hpp file.


@Gilad Kahn


