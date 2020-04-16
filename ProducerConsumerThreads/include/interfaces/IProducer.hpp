#ifndef PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_IPRODUCER_HPP

#include <queue>

namespace DataFlow {
template<class T>
class IProducer {
public:
    virtual ~IProducer() = default;

    [[nodiscard]] virtual T FillContainer() = 0;
    virtual void InsertIntoQueue() = 0;
    virtual void Run() = 0;
};
} // namespace DataFlow

#endif // PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
