#ifndef PRODUCERCONSUMERMPI_PRODUCER_TPP
#define PRODUCERCONSUMERMPI_PRODUCER_TPP

#include "GenericOstreamOperators.hpp"
#include "Mpi.hpp"
#include "Timer.hpp"
#include <Producer.hpp>
#include <algorithm>
#include <iostream>
#include <unistd.h>

namespace MPI {

template<class T>
Producer<T>::Producer(std::size_t noElements,
                      CommonCommunicator<T>& communicator) :
    noElements_{noElements},
    communicator_{communicator} {}

template<class T>
void Producer<T>::Run() {
    std::ofstream comparisonFile{PROJECT_SOURCE_DIR "/logs/comparison.txt",
                                 std::ios::app};
    comparisonFile << "Build info: " BUILD_INFO "\n";
    Timer timer{comparisonFile};
    T stop{communicator_.GetLimit()};
    for (; iteration_ < noElements_; iteration_++) {
        InsertIntoQueue();
    }
    for (std::size_t i = 1; i < size_; i++) {
        communicator_.ISend(static_cast<int>(i), stop);
    }
    comparisonFile << '\n';
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
    if (iteration_ < size_ - 1) {
        T temp{FillContainer()};
        std::cout << iteration_ + 1 << "): " << CalculateMean(temp) << '\n';
        communicator_.ISend(static_cast<int>(iteration_ + 1), FillContainer());
    } else {
        CheckConsumerAccessibility();
    }
}

template<class T>
void Producer<T>::CheckConsumerAccessibility() {
    MPI::Request request{};
    std::size_t destination{};
    if (isReadyToReceive_) {
        request = communicator_.IRecv(MPI_ANY_SOURCE, destination);
        isReadyToReceive_ = false;
    }
    if (request.Test()) {
        SendMessage(destination);
        isReadyToReceive_ = true;
    } else {
        queue_.push(FillContainer());
        iteration_--;
    }
}

template<class T>
void Producer<T>::SendMessage(std::size_t destination) {
    if (queue_.empty()) {
        //        std::cout << destination << "): " << CalculateMean(temp) <<
        //        '\n';
        communicator_.ISend(static_cast<int>(destination), FillContainer());
    } else {
        hack_ = queue_.front();
        communicator_.ISend(static_cast<int>(destination), T{hack_});
        queue_.pop();
        iteration_--;
    }
}

template<class T>
double Producer<T>::CalculateMean(const T& element) {
    return std::accumulate(std::begin(element), std::end(element), 0) /
           static_cast<double>(element.size());
}
} // namespace MPI
#endif // PRODUCERCONSUMERMPI_PRODUCER_TPP
