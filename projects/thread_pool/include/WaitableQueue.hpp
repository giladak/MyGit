// dev    : Gilad Kahn
// rev    : Sara Shushan
// date   : 14.6.22
// status : approved



#ifndef __ILRD_RD1167_WAITABLE_QUEUE_HPP__
#define __ILRD_RD1167_WAITABLE_QUEUE_HPP__

#include <chrono>             // for milliseconds
#include <mutex>              // for mutex
#include <condition_variable> // for condition variable



namespace ilrd
{
    template<typename Container>
    using ValueType = typename Container::value_type;

template<typename Container>
class WaitableQueue 
{
    /*
     *  Container requires:
     *      1. 'push' method
     *      2. 'pop' method
     *      3. access to first method
     *      4. 'empty' method
     * 
     *  T requires:
     *      1. is copyable
     *      2. is moveable
     */

public:
    explicit WaitableQueue() = default;
    ~WaitableQueue() = default;
    WaitableQueue(const WaitableQueue &other_) = delete;
    WaitableQueue& operator=(const WaitableQueue &other_) = delete;


    void Push(ValueType<Container>& value_) noexcept;
    bool Pop(ValueType<Container>& out_, std::chrono::milliseconds time_out) noexcept;
    void Pop(ValueType<Container>& out_) noexcept;
    void Peek(ValueType<Container>& out_) const noexcept;
    bool IsEmpty(void) const noexcept;

private:
    Container m_container;
    mutable std::recursive_mutex m_lock; // use lock_guard (?)
    mutable std::condition_variable_any m_cv;

    ValueType<Container> front();
    void WaitForPush() noexcept;

};

/* -------------------------------------------------------------------------- */
//!                               implementitions                             */
/* -------------------------------------------------------------------------- */

template<typename Container>
void WaitableQueue<Container>::Push(ValueType<Container>& value_) noexcept
{
    std::unique_lock<std::recursive_mutex> scope_lock(m_lock);

    m_container.push(value_);

    m_cv.notify_one();
}

template<typename Container>
bool WaitableQueue<Container>::Pop(ValueType<Container>& out_, std::chrono::milliseconds time_out) noexcept
{
    std::unique_lock<std::recursive_mutex> scope_lock(m_lock);

    if (true == IsEmpty())
    {
        if (false == m_cv.wait_for(scope_lock, time_out, []{return(false);}))
        {
            return (1);
        }
    }

    out_ = m_container.front();
    m_container.pop();

    return(0);
}

template<typename Container>
void WaitableQueue<Container>::Pop(ValueType<Container>& out_) noexcept
{
    std::unique_lock<std::recursive_mutex> scope_lock(m_lock);

    WaitForPush();
    out_ = m_container.front();
    m_container.pop();
}

template<typename Container>
void WaitableQueue<Container>::Peek(ValueType<Container>& out_) const noexcept
{
    std::unique_lock<std::recursive_mutex> scope_lock(m_lock);

    WaitForPush();

    out_ = m_container.front();
}

template<typename Container>
bool WaitableQueue<Container>::IsEmpty() const noexcept
{
    std::unique_lock<std::recursive_mutex> scope_lock(m_lock);

    return(m_container.empty());
}



/* ------------------------------ help function ----------------------------- */


template<typename Container>
void WaitableQueue<Container>::WaitForPush() noexcept
{
    // if (true == IsEmpty())
    // {
    //     m_cv.wait(m_lock);
    // }

    m_cv.wait(m_lock, [&]{return (false == IsEmpty());});

}





} // ilrd namespace end

#endif //__ILRD_RD1167_WAITABLE_QUEUE_HPP__