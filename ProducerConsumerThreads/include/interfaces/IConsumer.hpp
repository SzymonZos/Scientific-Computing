#ifndef PRODUCERCONSUMERTHREADS_ICONSUMER_HPP
#define PRODUCERCONSUMERTHREADS_ICONSUMER_HPP

#include <cstdint>
#include <queue>

namespace DataFlow {
    template<class T>
    class IConsumer {
    public:
        virtual ~IConsumer() = default;

        virtual void SortElement() = 0;
        virtual T TakeFromQueue() = 0;
        virtual void Run() = 0;
    };
}

#endif //PRODUCERCONSUMERTHREADS_ICONSUMER_HPP
