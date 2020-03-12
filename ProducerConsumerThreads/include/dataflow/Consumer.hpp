#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_HPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_HPP

#include "interfaces/IConsumer.hpp"

namespace DataFlow {
    template<class T>
    class Consumer : public IConsumer<T> {

    };
}

#include "impl/Consumer.tpp"

#endif //PRODUCERCONSUMERTHREADS_CONSUMER_HPP
