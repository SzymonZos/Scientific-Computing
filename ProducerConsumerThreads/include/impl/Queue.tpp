#ifndef PRODUCERCONSUMERTHREADS_QUEUE_TPP
#define PRODUCERCONSUMERTHREADS_QUEUE_TPP

namespace DataFlow {
template<class T, std::size_t size>
bool Queue<T, size>::IsEmpty() const {
    return queue_.empty();
}

template<class T, std::size_t size>
typename Queue<T, size>::size_type Queue<T, size>::Size() const {
    return queue_.size();
}

template<class T, std::size_t size>
typename Queue<T, size>::reference Queue<T, size>::Front() {
    std::lock_guard lock(mutex_);
    return queue_.front();
}

template<class T, std::size_t size>
typename Queue<T, size>::const_reference Queue<T, size>::Front() const {
    return queue_.front();
}

template<class T, std::size_t size>
typename Queue<T, size>::reference Queue<T, size>::Back() {
    std::lock_guard lock(mutex_);
    return queue_.back();
}

template<class T, std::size_t size>
typename Queue<T, size>::const_reference Queue<T, size>::Back() const {
    return queue_.back();
}

template<class T, std::size_t size>
void Queue<T, size>::Push(const value_type& value) {
    std::lock_guard lock(mutex_);
    if (noElements_ >= size) {
        throw std::length_error("Queue is full!");
    }
    noElements_++;
    queue_.push(value);
}

template<class T, std::size_t size>
void Queue<T, size>::Push(value_type&& value) {
    std::lock_guard lock(mutex_);
    if (noElements_ >= size) {
        throw std::length_error("Queue is full!");
    }
    noElements_++;
    queue_.push(std::move(value));
}

template<class T, std::size_t size>
template<typename... Args>
decltype(auto) Queue<T, size>::Emplace(Args... args) {
    std::lock_guard lock(mutex_);
    if (noElements_ + sizeof...(Args) > size) {
        throw std::length_error("Attempted to emplace too many elements!");
    }
    noElements_ += sizeof...(Args);
    return queue_.emplace(std::forward<Args>(args)...);
}

template<class T, std::size_t size>
void Queue<T, size>::Pop() {
    std::lock_guard lock(mutex_);
    if (!noElements_) {
        throw std::domain_error("Queue is empty!");
    }
    noElements_--;
    queue_.pop();
}

template<class T, std::size_t size>
std::ostream& operator<<(std::ostream& stream,
                         const DataFlow::Queue<T, size>& queue) {
    stream << "[";
    for (const auto& value : queue.Back()) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}
} // namespace DataFlow

#endif // PRODUCERCONSUMERTHREADS_QUEUE_TPP