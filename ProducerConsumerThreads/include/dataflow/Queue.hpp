#ifndef PRODUCERCONSUMERTHREADS_QUEUE_HPP
#define PRODUCERCONSUMERTHREADS_QUEUE_HPP

#include <queue>
#include <ostream>
#include "forward/queue_fwd.hpp"

namespace DataFlow {
    template<class T, size_t size = 10>
    class Queue {
    private:
        std::queue<T> queue_;

    public:
        std::queue<T>& GetQueue();
        friend std::ostream& operator<< <>(std::ostream& stream,
                                           const Queue<T>& queue);
    };
}

#include "impl/Queue.tpp"

#endif //PRODUCERCONSUMERTHREADS_QUEUE_HPP
