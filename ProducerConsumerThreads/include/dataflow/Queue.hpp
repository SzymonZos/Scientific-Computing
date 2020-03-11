#ifndef PRODUCERCONSUMERTHREADS_QUEUE_HPP
#define PRODUCERCONSUMERTHREADS_QUEUE_HPP

#include <queue>
#include <ostream>

namespace DataFlow {

    template<class T>
    class Queue;

    template<class T>
    std::ostream& operator<<(std::ostream& stream, const Queue<T>& queue);

    template<class T>
    class Queue {
    private:
        std::queue<T> queue_;

    public:
        std::queue<T>& GetQueue() {
            return queue_;
        }

        friend std::ostream& operator<< <>(std::ostream& stream,
                                           const Queue<T>& queue);
    };
}

#include "impl/Queue.tpp"

#endif //PRODUCERCONSUMERTHREADS_QUEUE_HPP
