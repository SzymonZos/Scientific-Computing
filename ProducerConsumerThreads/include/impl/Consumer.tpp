#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_TPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_TPP

#include <algorithm>

namespace DataFlow {

template<class T>
Consumer<T>::Consumer(std::shared_ptr<Queue<T>> pQueue) :
    pQueue_{pQueue},
    thread_{} {}

template<class T>
Consumer<T>::~Consumer() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

template<class T>
Consumer<T>& Consumer<T>::operator=(Consumer<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    if (thread_.joinable()) {
        thread_.join();
    }
    pQueue_ = std::move(other.pQueue_);
    thread_ = std::move(other.thread_);
    return *this;
}

template<class T>
void Consumer<T>::Run() {
    thread_ = std::thread{&Consumer<T>::SortElement, this};
}

template<class T>
void Consumer<T>::SortElement() {
    while (true) {
        try {
            T element = TakeFromQueue();
            std::sort(element.begin(), element.end());
            std::lock_guard lock(ostreamMutex_);
            std::cout << std::this_thread::get_id() << ": " << element << "\n";
        } catch (const std::exception& exception) {
            std::lock_guard lock(ostreamMutex_);
            std::cout << "Caught exception: " << exception.what() << "\n";
            if (pQueue_->isProducerDone) {
                break;
            } else {
                std::this_thread::yield();
            }
        }
    }
}

template<class T>
T Consumer<T>::TakeFromQueue() {
    std::lock_guard lock(queueMutex_);
    T element = pQueue_->Front();
    pQueue_->Pop();
    return element;
}
} // namespace DataFlow

#endif // PRODUCERCONSUMERTHREADS_CONSUMER_TPP