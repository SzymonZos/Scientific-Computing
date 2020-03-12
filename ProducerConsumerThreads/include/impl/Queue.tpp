#ifndef PRODUCERCONSUMERTHREADS_QUEUE_TPP
#define PRODUCERCONSUMERTHREADS_QUEUE_TPP

template <class T, size_t size>
std::queue<T>& DataFlow::Queue<T, size>::GetQueue() {
    return queue_;
}

template <class T, size_t size>
std::ostream& DataFlow::operator<<(std::ostream& stream,
                                   const DataFlow::Queue<T, size>& queue) {
    stream << "[";
    for (const auto& value : queue.queue_.front()) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}

#endif //PRODUCERCONSUMERTHREADS_QUEUE_TPP