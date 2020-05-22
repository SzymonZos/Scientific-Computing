#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_TPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_TPP

#include <algorithm>
#include <iostream>
#include "Mpi.hpp"

namespace MPI {
template<class T>
Producer<T>::Producer(std::size_t noElements) : noElements_{noElements} {}

template<class T>
void Producer<T>::Run() {}

template<class T>
T Producer<T>::FillContainer() {
    T element;
    std::generate(std::begin(element), std::end(element), [&] {
        return distribution_(rng_);
    });
    return element;
}

template<class T>
void Producer<T>::InsertIntoQueue() {
    for (uint32_t iteration = 0; iteration < noElements_; iteration++) {
    }
}
} // namespace MPI
#endif // PRODUCERCONSUMERTHREADS_PRODUCER_TPP