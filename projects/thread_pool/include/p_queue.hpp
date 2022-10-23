#ifndef __ILRD_RD1167_P_QUEUE_HPP__
#define __ILRD_RD1167_P_QUEUE_HPP__

#include <vector>    //vector
#include <queue>     //queue

namespace ilrd
{

template<typename _Tp, typename _Sequence = std::vector<_Tp>,
        typename _Compare  = std::less<typename _Sequence::value_type> >
class PriorityQueue : private std::priority_queue<_Tp, _Sequence, _Compare>
{
public:
    using std::priority_queue<_Tp, _Sequence, _Compare>::value_type;

    using std::priority_queue<_Tp, _Sequence, _Compare>::empty;
    using std::priority_queue<_Tp, _Sequence, _Compare>::push;
    using std::priority_queue<_Tp, _Sequence, _Compare>::pop;
    using std::priority_queue<_Tp, _Sequence, _Compare>::size;


    inline typename _Sequence::const_reference front() const;
};


template<typename _Tp, typename _Sequence, typename _Compare>
inline typename _Sequence::const_reference
PriorityQueue<_Tp, _Sequence, _Compare>::front() const
{
    return this->top();
}


} // ilrd

#endif //PRIORITY_QUEUE_H