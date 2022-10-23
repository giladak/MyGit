// dev    : Gilad Kahn
// rev    : 
// date   : 
// status : 



#ifndef __ILRD_RD1167_SINGELTON_HPP__
#define __ILRD_RD1167_SINGELTON_HPP__


namespace ilrd
{
// to use this class you need  to set your class ctor as private and default, and the make singleton class friend of your class 

template <typename T>
class Singleton
{
public:
    static T& GetInstance();
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
  Singleton(){};
 
};


template<typename T>
T& Singleton<T>::GetInstance()
{
    static T s;
    return s;
}

}//ilrd

#endif // __ILRD_RD1167_SINGELTON_H