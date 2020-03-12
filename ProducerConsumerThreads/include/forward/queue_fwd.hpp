#ifndef PRODUCERCONSUMERTHREADS_QUEUE_FWD_HPP
#define PRODUCERCONSUMERTHREADS_QUEUE_FWD_HPP

namespace DataFlow {
    template<class T, size_t size>
    class Queue;

    template<class T, size_t size>
    std::ostream& operator<<(std::ostream& stream, const Queue<T, size>& queue);
}
#endif //PRODUCERCONSUMERTHREADS_QUEUE_FWD_HPP
