#ifndef PRODUCERCONSUMERMPI_CONSUMER_TPP
#define PRODUCERCONSUMERMPI_CONSUMER_TPP

#include "Mpi.hpp"
#include <Consumer.hpp>
#include <algorithm>
#include <iostream>
#include <numeric>

namespace MPI {
template<class T>
Consumer<T>::Consumer(CommonCommunicator<T>& communicator) :
    communicator_{communicator} {}

template<class T>
void Consumer<T>::Run() {
    while (true) {
        element_ = TakeFromQueue();
        if (communicator_.IsLastMsg(element_)) {
            std::cout << rank_ << ") Sorted: " << noSortedElements_ << '\n';
            break;
        }
        SortElement();
        communicator_.ISend(0, rank_);
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
    std::cout << rank_ << ") Mean: " << mean << '\n';
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

#endif // PRODUCERCONSUMERMPI_CONSUMER_TPP
