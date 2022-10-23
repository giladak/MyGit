#ifndef TEST_HPP
#define TEST_HPP


#include <ctime>        //clock
#include <mutex>        // for mutex



#include "utilities.hpp"


#define START_TEST(function_name) \
    static size_t testnum = 0; \
    static size_t tests_passed = 0; \
    static size_t tests_failed = 0; \
    std::mutex lock;\
    MGNB(std::cout << "tests for : " << function_name << "\t: " <<std::endl;);


#define IF(test_name, answer, input)  if(answer != input) \
    {TEST_FAILED(test_name, answer, input)}\
else\
{TEST_PASSED}\
++testnum;


#define TEST_PASSED ++tests_passed;

#define TEST_FAILED(test_name, answer, input) \
lock.lock();\
RED(std::cout << "error in function: " << test_name << "\t in testnum : " << testnum <<std::endl;);\
RED(std::cout << "\tat line: " << __LINE__<< "\tat file: " << __FILENAME__  << std::endl;);\
RED(std::cout << "given answer : " << input << "\t wanted answer : " << answer << std::endl;);\
++tests_failed;\
lock.unlock();


#define END_TEST \
    lock.lock();\
    GRN(std::cout << "\n\n\tnumber of tests passed: " << tests_passed << std::endl;);\
    RED(std::cout << "\tnumber of tests failed: " << tests_failed << std::endl;);\
    tests_passed = 0;\
    tests_failed = 0;\
    std::cout << "\n\n" << std::endl;\
    lock.unlock();




#define CPU_TIME_MESSURE_START clock_t begin = clock()
#define CPU_TIME_MESSURE_END clock_t end = clock()
#define CPU_TIME_MESSURE_ANSWER static_cast<clock_t>(end - begin)
#define CPU_TIME_MESSURE_PRINT(content)  std ::cout << content << ": \t " << CPU_TIME_MESSURE_ANSWER << std::endl;




#define TIME_MESSURE_START time_t begin = time(NULL)
#define TIME_MESSURE_END time_t end = time(NULL)
#define TIME_MESSURE_ANSWER static_cast<time_t>(end - begin)
#define TIME_MESSURE_PRINT(content)  std ::cout << content << ": \t " << TIME_MESSURE_ANSWER << std::endl;




#endif //TEST_HPP