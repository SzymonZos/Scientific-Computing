#ifndef PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_IPRODUCER_HPP

#include <cstdint>
#include <queue>

namespace DataFlow {
    template<class T>
    class IProducer {
    public:
        IProducer() = default;
        virtual ~IProducer() = default;

        virtual void GenerateRandomNumbers() = 0;
        virtual void InsertIntoQueue(std::queue<T>& queue) = 0;
    };
}

#endif //PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
