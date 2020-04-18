#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_TPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_TPP

#include <algorithm>

namespace DataFlow {
template<class T, std::size_t size>
Producer<T, size>::Producer(std::size_t noElements,
                            std::shared_ptr<Queue<T, size>> pQueue) :
    noElements_{noElements},
    pQueue_{pQueue} {}

template<class T, std::size_t size>
Producer<T, size>::~Producer() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

template<class T, std::size_t size>
Producer<T, size>::Producer(Producer<T, size>&& other) noexcept :
    noElements_{other.noElements_},
    pQueue_{std::move(other.pQueue_)},
    thread_{std::move(other.thread_)} {
    other.noElements_ = 0;
}

template<class T, std::size_t size>
Producer<T, size>&
Producer<T, size>::operator=(Producer<T, size>&& other) noexcept {
    if (this != &other) {
        if (thread_.joinable()) {
            thread_.join();
        }
        noElements_ = other.noElements_;
        pQueue_ = std::move(other.pQueue_);
        thread_ = std::move(other.thread_);
        other.noElements_ = 0;
    }
    return *this;
}

template<class T, std::size_t size>
void Producer<T, size>::Run() {
    if (!pQueue_) {
        throw(std::runtime_error{"Producer: pQueue_ is nullptr."});
    }
    if (!thread_.joinable()) {
        thread_ = std::thread{&Producer<T, size>::InsertIntoQueue, this};
    }
}

template<class T, std::size_t size>
T Producer<T, size>::FillContainer() {
    T element;
    std::generate(std::begin(element), std::end(element), [&] {
        return distribution_(rng_);
    });
    return element;
}

template<class T, std::size_t size>
void Producer<T, size>::InsertIntoQueue() {
    for (uint32_t iteration = 0; iteration < noElements_; iteration++) {
        try {
            pQueue_->Push(FillContainer());
        } catch (const std::length_error& exception) {
            iteration--;
            std::this_thread::yield();
        } catch (const std::exception& exception) {
            std::cout << "Caught exception: " << exception.what() << "\n";
        } catch (...) {
            std::cout << "Caught unknown exception\n";
        }
    }
    pQueue_->isProducerDone_ = true;
}
} // namespace DataFlow
#endif // PRODUCERCONSUMERTHREADS_PRODUCER_TPP