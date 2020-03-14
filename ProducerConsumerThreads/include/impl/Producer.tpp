#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_TPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_TPP

#include <random>
#include <dataflow/Producer.hpp>

namespace DataFlow {
    template<class T>
    Producer<T>::Producer(uint32_t noElements,
                          std::shared_ptr<Queue<T>> pQueue) :
            noElements_{noElements},
            pQueue_{pQueue} {}

    template<class T>
    int32_t Producer<T>::GenerateRandomNumber() {
        std::random_device randomDevice;
        std::mt19937 randomNumberGenerator(randomDevice());
        std::uniform_int_distribution<std::mt19937::result_type>
                distribution(minRandomNumber, maxRandomNumber);
        return distribution(randomNumberGenerator);
    }

    template<class T>
    T Producer<T>::FillContainer() {
        T element;
        for (auto& number : element) {
            number = GenerateRandomNumber();
        }
        return element;
    }

    template<class T>
    void Producer<T>::InsertIntoQueue() {
        pQueue_->Push(FillContainer());
    }
}
#endif //PRODUCERCONSUMERTHREADS_PRODUCER_TPP