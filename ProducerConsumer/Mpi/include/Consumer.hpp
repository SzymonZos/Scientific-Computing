#ifndef PRODUCERCONSUMERMPI_CONSUMER_HPP
#define PRODUCERCONSUMERMPI_CONSUMER_HPP

#include "IConsumer.hpp"
#include <cstddef>
#include "Mpi.hpp"

namespace MPI {
template<class T>
class Consumer : public IConsumer<T> {
public:
    Consumer() = default;
    virtual ~Consumer() = default;

    Consumer(const Consumer& other) = delete;
    Consumer& operator=(const Consumer& other) = delete;

    // WARNING: This class is NOT movable after using method Run()
    Consumer(Consumer&& other) noexcept = default;
    Consumer& operator=(Consumer&& other) noexcept = default;

    void Run() override;

private:
    std::size_t noSortedElements_{};

    void SortElement() override;
    T TakeFromQueue() override;
    double CalculateMean(const T& element) override;
};
} // namespace MPI

#include "impl/Consumer.tpp"

#endif // PRODUCERCONSUMERMPI_CONSUMER_HPP
