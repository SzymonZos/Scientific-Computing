#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_TPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_TPP

#include <algorithm>

namespace DataFlow {

template<class T, std::size_t size>
Consumer<T, size>::Consumer(std::shared_ptr<Queue<T, size>> pQueue) :
    pQueue_{pQueue} {}

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
            auto mean = CalculateMean(element);
            std::sort(std::begin(element), std::end(element));
            noSortedElements_++;
            std::lock_guard lock(ostreamMutex_);
            std::cout << std::this_thread::get_id() << ": " << mean << "\n";
        } catch (const std::length_error& exception) {
            if (pQueue_->isProducerDone_) {
                std::cout << "Sorted: " << std::this_thread::get_id() << ": "
                          << noSortedElements_ << "\n";
                break;
            }
            std::this_thread::yield();
        } catch (const std::exception& exception) {
            std::cout << "Caught exception: " << exception.what() << "\n";
        } catch (...) {
            std::cout << "Caught unknown exception\n";
        }
    }
}

template<class T, std::size_t size>
T Consumer<T, size>::TakeFromQueue() {
    std::lock_guard lock(queueMutex_);
    T element = pQueue_->Front();
    pQueue_->Pop();
    return element;
}

template<class T, std::size_t size>
double Consumer<T, size>::CalculateMean(const T& element) {
    return std::accumulate(std::begin(element), std::end(element), 0) /
           static_cast<double>(element.size());
}
} // namespace DataFlow

#endif // PRODUCERCONSUMERTHREADS_CONSUMER_TPP