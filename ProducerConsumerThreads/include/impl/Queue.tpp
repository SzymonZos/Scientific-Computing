#ifndef PRODUCERCONSUMERTHREADS_QUEUE_TPP
#define PRODUCERCONSUMERTHREADS_QUEUE_TPP

template <class T>
std::ostream& DataFlow::operator<<(std::ostream& stream,
                                   const DataFlow::Queue<T>& queue) {
    stream << "[";
    for (const auto& value : queue.queue_.front()) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}

#endif //PRODUCERCONSUMERTHREADS_QUEUE_TPP