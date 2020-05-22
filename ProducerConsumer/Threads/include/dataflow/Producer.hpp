#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_HPP

#include "IProducer.hpp"
#include "utils/Constants.hpp"
#include <memory>
#include <random>
#include <thread>

namespace DataFlow {
template<class T, std::size_t size = Constants::defaultQueueSize>
class Producer : public IProducer<T> {
public:
    using value_type = typename T::value_type;
    explicit Producer(std::size_t noElements,
                      std::shared_ptr<Queue<T, size>> pQueue);

    Producer() = default;
    ~Producer() override;

    Producer(const Producer& other) = delete;
    Producer& operator=(const Producer& other) = delete;

    // WARNING: This class is NOT movable after using method Run()
    Producer(Producer&& other) noexcept;
    Producer& operator=(Producer&& other) noexcept;

    void Run() override;

private:
    static const value_type minRandomNumber{-50'000};
    static const value_type maxRandomNumber{50'000};

    std::mt19937 rng_{std::random_device{}()};
    std::uniform_int_distribution<value_type> distribution_{minRandomNumber,
                                                            maxRandomNumber};
    std::size_t noElements_{};
    std::shared_ptr<Queue<T, size>> pQueue_{};
    std::thread thread_{};

    [[nodiscard]] T FillContainer() override;
    void InsertIntoQueue() override;
};
} // namespace DataFlow

#include "impl/Producer.tpp"

#endif // PRODUCERCONSUMERTHREADS_PRODUCER_HPP
