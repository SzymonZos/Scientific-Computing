#ifndef PRODUCERCONSUMERTHREADS_QUEUE_FWD_HPP
#define PRODUCERCONSUMERTHREADS_QUEUE_FWD_HPP

#include <ostream>

namespace DataFlow {
template<class T, std::size_t size>
class Queue;

template<class T, std::size_t size>
std::ostream& operator<<(std::ostream& stream, const Queue<T, size>& queue);
} // namespace DataFlow
#endif // PRODUCERCONSUMERTHREADS_QUEUE_FWD_HPP
