
#ifndef UTILITIES_HPP
#define UTILITIES_HPP


#include <cstring> //strchr
#include <string> //string
#include <stdio.h> //printf


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define RED(x)         printf("\033[0;31m"); x; printf("\033[0m")
#define GRN(x)         printf("\033[0;32m"); x; printf("\033[0m")
#define MGNB(x)        printf("\033[0;45m"); x; printf("\033[0m")


#if __cplusplus<201104
#define noexcept throw()
#endif



#endif //UTILITIES_HPP



//functions for


// std::string ConvertToString(int num);
