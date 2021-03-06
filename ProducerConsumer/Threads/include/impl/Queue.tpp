#ifndef SCIENTIFICCOMPUTING_PRODUCERCONSUMERTHREADS_QUEUE_TPP
#define SCIENTIFICCOMPUTING_PRODUCERCONSUMERTHREADS_QUEUE_TPP

namespace DataFlow {
template<class T, std::size_t size>
bool Queue<T, size>::IsEmpty() const {
    std::lock_guard lock(elementMutex_);
    return !noElements_;
}

template<class T, std::size_t size>
size_type<T> Queue<T, size>::Size() const {
    std::lock_guard lock(elementMutex_);
    return noElements_;
}

template<class T, std::size_t size>
void Queue<T, size>::HandleEmpty() const {
    if (!noElements_) {
        throw std::length_error("Queue is empty.");
    }
}

template<class T, std::size_t size>
void Queue<T, size>::HandleFull() const {
    if (noElements_ >= size) {
        throw std::length_error("Queue is full.");
    }
}

template<class T, std::size_t size>
reference<T> Queue<T, size>::Front() {
    std::lock_guard lock(elementMutex_);
    HandleEmpty();
    return queue_.front();
}

template<class T, std::size_t size>
const_reference<T> Queue<T, size>::Front() const {
    std::lock_guard lock(elementMutex_);
    HandleEmpty();
    return queue_.front();
}

template<class T, std::size_t size>
reference<T> Queue<T, size>::Back() {
    std::lock_guard lock(elementMutex_);
    HandleEmpty();
    return queue_.back();
}

template<class T, std::size_t size>
const_reference<T> Queue<T, size>::Back() const {
    std::lock_guard lock(elementMutex_);
    HandleEmpty();
    return queue_.back();
}

template<class T, std::size_t size>
void Queue<T, size>::Push(const value_type<T>& value) {
    std::lock_guard lock(elementMutex_);
    HandleFull();
    queue_.push(value);
    noElements_++;
}

template<class T, std::size_t size>
void Queue<T, size>::Push(value_type<T>&& value) {
    std::lock_guard lock(elementMutex_);
    HandleFull();
    queue_.push(std::move(value));
    noElements_++;
}

template<class T, std::size_t size>
template<typename... Args>
decltype(auto) Queue<T, size>::Emplace(Args... args) {
    std::lock_guard lock(elementMutex_);
    if (noElements_ + sizeof...(Args) > size) {
        throw std::length_error("Attempted to emplace too many elements.");
    }
    noElements_ += sizeof...(Args);
    return queue_.emplace(std::forward<Args>(args)...);
}

template<class T, std::size_t size>
void Queue<T, size>::Pop() {
    std::lock_guard lock(elementMutex_);
    HandleEmpty();
    queue_.pop();
    noElements_--;
}

template<class T, std::size_t size>
std::ostream& operator<<(std::ostream& stream,
                         const DataFlow::Queue<T, size>& queue) {
    stream << "[";
    for (auto value : queue.Back()) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}
} // namespace DataFlow

#endif // SCIENTIFICCOMPUTING_PRODUCERCONSUMERTHREADS_QUEUE_TPP