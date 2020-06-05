#ifndef PRODUCERCONSUMERMPI_PRODUCER_TPP
#define PRODUCERCONSUMERMPI_PRODUCER_TPP

#include "GenericOstreamOperators.hpp"
#include "Mpi.hpp"
#include "Timer.hpp"
#include <Producer.hpp>
#include <algorithm>
#include <iostream>
#include <new>
#include <unistd.h>

namespace MPI {

template<class T>
Producer<T>::Producer(std::size_t noElements,
                      CommonCommunicator<T>& communicator) :
    noElements_{noElements},
    communicator_{communicator} {
    queue_.reserve(queueSize_);
}

template<class T>
void Producer<T>::Run() {
    std::ofstream comparisonFile{PROJECT_SOURCE_DIR "/logs/comparison.txt",
                                 std::ios::app};
    comparisonFile << "Build info: " BUILD_INFO "\n";
    Timer timer{comparisonFile};
    T stop{communicator_.GetLimit()};
    while (iteration_ < noElements_) {
        InsertIntoQueue();
    }
    for (std::size_t i = 1; i < size_; i++) {
        SendMessage(i, stop);
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
    const auto position = iteration_ % queueSize_;
    new (&queue_[position]) T{FillContainer()};
    //    queue_[position] = std::move(FillContainer());
    if (iteration_ < size_ - 1) {
        SendMessage(++iteration_, queue_[position]);
    } else {
        CheckConsumerAccessibility(position);
    }
}

template<class T>
void Producer<T>::CheckConsumerAccessibility(const std::size_t position) {
    if (isReadyToReceive_) {
        request_ = communicator_.IRecv(MPI_ANY_SOURCE, destination_);
        isReadyToReceive_ = false;
    }
    if (request_.Test()) {
        SendMessage(destination_, queue_[position]);
        isReadyToReceive_ = true;
        iteration_++;
    }
}

template<class T>
void Producer<T>::SendMessage(std::size_t destination, const T& msg) {
    communicator_.ISend(static_cast<int>(destination), msg);
}
} // namespace MPI
#endif // PRODUCERCONSUMERMPI_PRODUCER_TPP
