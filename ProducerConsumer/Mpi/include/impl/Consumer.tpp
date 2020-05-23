#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_TPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_TPP

#include "Mpi.hpp"
#include <Consumer.hpp>
#include <algorithm>
#include <iostream>
#include <numeric>

namespace MPI {
template<class T>
void Consumer<T>::Run() {
    const auto rank = static_cast<std::size_t>(communicator_.GetRank());
    const auto limit = std::numeric_limits<typename T::value_type>::max();
    while (true) {
        element_ = TakeFromQueue();
        if (element_[0] == limit) {
            std::cout << rank << " sorted: " << noSortedElements_ << '\n';
            break;
        }
        SortElement();
        communicator_.ISend(0, rank);
    }
}

template<class T>
std::size_t Consumer<T>::GetNoSortedElements() {
    return noSortedElements_;
}

template<class T>
void Consumer<T>::SortElement() {
    auto mean = CalculateMean(element_);
    std::sort(std::begin(element_), std::end(element_));
    noSortedElements_++;
    std::cout << communicator_.GetRank() << " Mean: " << mean << '\n';
}

template<class T>
T Consumer<T>::TakeFromQueue() {
    T element;
    MPI::Request recv{communicator_.IRecv(0, element)};
    recv.Wait();
    return element;
}

template<class T>
double Consumer<T>::CalculateMean(const T& element) {
    return std::accumulate(std::begin(element), std::end(element), 0) /
           static_cast<double>(element.size());
}
} // namespace MPI

#endif // PRODUCERCONSUMERTHREADS_CONSUMER_TPP