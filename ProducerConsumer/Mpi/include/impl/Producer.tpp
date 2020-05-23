#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_TPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_TPP

#include "Mpi.hpp"
#include "Timer.hpp"
#include <algorithm>
#include <iostream>

namespace MPI {
template<class T>
Producer<T>::Producer(std::size_t noElements) : noElements_{noElements} {}

template<class T>
void Producer<T>::Run() {
    Timer timer{};
    const auto size = static_cast<std::size_t>(communicator_.GetSize());
    const auto limit = std::numeric_limits<typename T::value_type>::max();
    T stop{limit};
    for (; iteration_ < noElements_; iteration_++) {
        InsertIntoQueue();
    }
    for (std::size_t i = 1; i < size; i++) {
        communicator_.ISend(static_cast<int>(i), stop);
    }
}

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
    std::size_t destination{};
    const auto size = static_cast<std::size_t>(communicator_.GetSize());
    if (iteration_ < size - 1) {
        communicator_.ISend(static_cast<int>(iteration_ + 1), FillContainer());
    } else {
        MPI::Request recv{communicator_.IRecv(MPI_ANY_SOURCE, destination)};
        recv.Wait();
        communicator_.ISend(static_cast<int>(destination), FillContainer());
    }
}
} // namespace MPI
#endif // PRODUCERCONSUMERTHREADS_PRODUCER_TPP