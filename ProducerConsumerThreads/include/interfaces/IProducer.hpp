#ifndef PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_IPRODUCER_HPP

#include <cstdint>
#include <queue>

namespace DataFlow {
    template<class T>
    class IProducer {
    public:
        virtual ~IProducer() = default;

        virtual int32_t GenerateRandomNumber() = 0;
        virtual T FillContainer() = 0;
        virtual void InsertIntoQueue() = 0;
    };
}

#endif //PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
