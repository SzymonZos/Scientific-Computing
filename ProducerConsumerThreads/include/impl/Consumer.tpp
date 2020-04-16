#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_TPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_TPP

#include <algorithm>

namespace DataFlow {

template<class T, std::size_t size>
Consumer<T, size>::Consumer(std::shared_ptr<Queue<T, size>> pQueue) :
    pQueue_{pQueue},
    thread_{} {}

template<class T, std::size_t size>
Consumer<T, size>::~Consumer() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

template<class T, std::size_t size>
Consumer<T, size>&
Consumer<T, size>::operator=(Consumer<T, size>&& other) noexcept {
    if (this != &other) {
        if (thread_.joinable()) {
            thread_.join();
        }
        pQueue_ = std::move(other.pQueue_);
        thread_ = std::move(other.thread_);
    }
    return *this;
}

template<class T, std::size_t size>
void Consumer<T, size>::Run() {
    if (!pQueue_) {
        throw(std::runtime_error{"Consumer: pQueue_ is nullptr."});
    }
    if (!thread_.joinable()) {
        thread_ = std::thread{&Consumer<T, size>::SortElement, this};
    }
}

template<class T, std::size_t size>
void Consumer<T, size>::SortElement() {
    while (true) {
        try {
            T element = TakeFromQueue();
            std::sort(std::begin(element), std::end(element));
            std::lock_guard lock(ostreamMutex_);
            std::cout << std::this_thread::get_id() << ": " << element << "\n";
        } catch (const std::length_error& exception) {
            std::lock_guard lock(ostreamMutex_);
            std::cout << "Caught exception: " << exception.what() << "\n";
            if (pQueue_->isProducerDone_) {
                break;
            } else {
                std::this_thread::yield();
            }
        } catch (const std::exception& exception) {
            std::cout << "Caught exception: " << exception.what() << "\n";
        } catch (...) {
            std::cout << "Caught unknown exception\n";
        }
    }
}

template<class T, std::size_t size>
T Consumer<T, size>::TakeFromQueue() {
    T element{};
    if (pQueue_) {
        std::lock_guard lock(queueMutex_);
        element = pQueue_->Front();
        pQueue_->Pop();
    }
    return element;
}
} // namespace DataFlow

#endif // PRODUCERCONSUMERTHREADS_CONSUMER_TPP