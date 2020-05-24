#ifndef PRODUCERCONSUMERMPI_CONSUMER_HPP
#define PRODUCERCONSUMERMPI_CONSUMER_HPP

#include "CommonCommunicator.hpp"
#include "IConsumer.hpp"
#include "Mpi.hpp"
#include <cstddef>

namespace MPI {
template<class T>
class Consumer : public IConsumer<T> {
public:
    explicit Consumer(CommonCommunicator<T>& communicator);

    Consumer() = delete;
    virtual ~Consumer() = default;

    Consumer(const Consumer& other) = delete;
    Consumer& operator=(const Consumer& other) = delete;

    // WARNING: This class is NOT movable after using method Run()
    Consumer(Consumer&& other) noexcept = default;
    Consumer& operator=(Consumer&& other) noexcept = default;

    void Run() override;
    std::size_t GetNoSortedElements();

private:
    std::size_t noSortedElements_{};
    CommonCommunicator<T>& communicator_;
    T element_{};
    std::size_t rank_{communicator_.template GetRank<std::size_t>()};

    void SortElement() override;
    T TakeFromQueue() override;
    double CalculateMean(const T& element) override;
};
} // namespace MPI

#include "impl/Consumer.tpp"

#endif // PRODUCERCONSUMERMPI_CONSUMER_HPP
