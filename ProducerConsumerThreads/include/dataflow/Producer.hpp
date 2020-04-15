#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_HPP

#include "interfaces/IProducer.hpp"
#include <cstdint>
#include <memory>
#include <random>
#include <thread>

namespace DataFlow {
template<class T, std::size_t size>
class Producer : public IProducer<T, size> {
public:
    explicit Producer(uint32_t noElements,
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
    static const int32_t minRandomNumber = -2048;
    static const int32_t maxRandomNumber = 2048;

    std::random_device randomDevice_{};
    std::mt19937 rng_{randomDevice_()};
    std::uniform_int_distribution<int32_t> distribution_{minRandomNumber,
                                                         maxRandomNumber};
    uint32_t noElements_ = 0;
    std::shared_ptr<Queue<T, size>> pQueue_;
    std::thread thread_;

    [[nodiscard]] T FillContainer() override;
    void InsertIntoQueue() override;
};
} // namespace DataFlow

#include "impl/Producer.tpp"

#endif // PRODUCERCONSUMERTHREADS_PRODUCER_HPP
