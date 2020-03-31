#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_TPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_TPP

#include <iostream>
#include <random>

namespace DataFlow {
template<class T>
Producer<T>::Producer(uint32_t noElements, std::shared_ptr<Queue<T>> pQueue) :
    noElements_{noElements},
    pQueue_{pQueue},
    thread_{} {}

template<class T>
Producer<T>::~Producer() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

template<class T>
Producer<T>::Producer(Producer<T>&& other) noexcept :
    noElements_{other.noElements_},
    pQueue_{std::move(other.pQueue_)},
    thread_{std::move(other.thread_)} {
    other.noElements_ = 0;
}

template<class T>
Producer<T>& Producer<T>::operator=(Producer<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    if (thread_.joinable()) {
        thread_.join();
    }
    noElements_ = other.noElements_;
    pQueue_ = std::move(other.pQueue_);
    thread_ = std::move(other.thread_);
    other.noElements_ = 0;
    return *this;
}

template<class T>
void Producer<T>::Run() {
    thread_ = std::thread{&Producer<T>::InsertIntoQueue, this};
}

template<class T>
int32_t Producer<T>::GenerateRandomNumber() const {
    std::random_device randomDevice;
    std::mt19937 randomNumberGenerator(randomDevice());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(
        minRandomNumber,
        maxRandomNumber);
    return distribution(randomNumberGenerator);
}

template<class T>
T Producer<T>::FillContainer() const {
    T element;
    for (auto& number : element) {
        number = GenerateRandomNumber();
    }
    return element;
}

template<class T>
void Producer<T>::InsertIntoQueue() {
    for (uint32_t iteration = 0; iteration < noElements_; iteration++) {
        try {
            pQueue_->Push(FillContainer());
            //                std::lock_guard lock(mutex_);
            std::cout << "Producer: " << *pQueue_ << "\n";
        } catch (const std::exception& exception) {
            std::cout << "Caught exception: " << exception.what() << "\n";
            iteration--; // Uncomment it when consumers are ready
            std::this_thread::yield();
        }
    }
    pQueue_->isProducerDone = true;
}
} // namespace DataFlow
#endif // PRODUCERCONSUMERTHREADS_PRODUCER_TPP