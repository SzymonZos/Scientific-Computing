#ifndef PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_IPRODUCER_HPP

#include <cstdint>
#include <queue>

namespace DataFlow {
template<class T>
class IProducer {
public:
    virtual ~IProducer() = default;

    [[nodiscard]] virtual int32_t GenerateRandomNumber() const = 0;
    [[nodiscard]] virtual T FillContainer() const = 0;
    virtual void InsertIntoQueue() = 0;
    virtual void Run() = 0;
};
} // namespace DataFlow

#endif // PRODUCERCONSUMERTHREADS_IPRODUCER_HPP
