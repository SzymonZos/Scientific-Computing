#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_TPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_TPP

#include "Mpi.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

namespace MPI {
template<class T>
void Consumer<T>::Run() {}

template<class T>
void Consumer<T>::SortElement() {
    T element = TakeFromQueue();
    auto mean = CalculateMean(element);
    std::sort(std::begin(element), std::end(element));
    noSortedElements_++;
    std::cout << "Mean: " << mean << "\n";
    std::cout << "Sorted: " << noSortedElements_ << "\n";
}

template<class T>
T Consumer<T>::TakeFromQueue() {
    T element;
    return element;
}

template<class T>
double Consumer<T>::CalculateMean(const T& element) {
    return std::accumulate(std::begin(element), std::end(element), 0) /
           static_cast<double>(element.size());
}
} // namespace MPI

#endif // PRODUCERCONSUMERTHREADS_CONSUMER_TPP