
#include <iostream>

#include "utilities.hpp"




std::string ConvertToString(int num)
{
    std::string answer = "";

    char buffer[100] = {0};


    sprintf(buffer, "%d", num);

    answer = buffer;

    return (answer);
}





