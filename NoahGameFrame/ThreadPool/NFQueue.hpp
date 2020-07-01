//
// Created by Administrator on 2020/6/26.
//

#ifndef DEBUG_DEAD_LOCK_NFQUEUE_H
#define DEBUG_DEAD_LOCK_NFQUEUE_H

#include "../Dep/concurrentqueue/concurrentqueue.h"
template <typename T>
class NFQueue: public moodycamel::ConcurrentQueue<T> {
public:
    NFQueue(){}
    virtual ~NFQueue(){}
    bool Push(const T&object)
    {
       return this->enqueue(object);
    }
    bool Pop(T &object)
    {
       return this->try_dequeue(object);
    }
};
#endif //DEBUG_DEAD_LOCK_NFQUEUE_H
