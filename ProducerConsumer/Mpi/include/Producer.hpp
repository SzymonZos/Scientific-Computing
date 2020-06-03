#ifndef PRODUCERCONSUMERMPI_PRODUCER_HPP
#define PRODUCERCONSUMERMPI_PRODUCER_HPP

#include "CommonCommunicator.hpp"
#include "IProducer.hpp"
#include "Mpi.hpp"
#include <queue>
#include <random>

namespace MPI {
template<class T>
class Producer : public IProducer<T> {
public:
    using value_type = typename T::value_type;
    explicit Producer(std::size_t noElements,
                      CommonCommunicator<T>& communicator);

    Producer() = delete;
    ~Producer() override = default;

    Producer(const Producer& other) = delete;
    Producer& operator=(const Producer& other) = delete;

    // WARNING: This class is NOT movable after using method Run()
    Producer(Producer&& other) noexcept = default;
    Producer& operator=(Producer&& other) noexcept = default;

    void Run() override;

private:
    static const value_type minRandomNumber{-50'000};
    static const value_type maxRandomNumber{50'000};

    std::mt19937 rng_{std::random_device{}()};
    std::uniform_int_distribution<value_type> distribution_{minRandomNumber,
                                                            maxRandomNumber};
    std::size_t noElements_{};
    CommonCommunicator<T>& communicator_;
    std::size_t iteration_{};
    std::size_t size_{communicator_.template GetSize<std::size_t>()};
    std::queue<T> queue_{};
    bool isReadyToReceive_{true};
    std::size_t destination_{};
    T hack_{};

    [[nodiscard]] T FillContainer() override;
    void InsertIntoQueue() override;
    void CheckConsumerAccessibility();
    void SendMessage(std::size_t destination);
    double CalculateMean(const T& element);
};
} // namespace MPI

#include "impl/Producer.tpp"

#endif // PRODUCERCONSUMERMPI_PRODUCER_HPP
