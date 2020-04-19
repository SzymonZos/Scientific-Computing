#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_HPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_HPP

#include "interfaces/IConsumer.hpp"
#include "utils/Constants.hpp"
#include <memory>
#include <mutex>
#include <thread>

namespace DataFlow {
template<class T, std::size_t size = Constants::defaultQueueSize>
class Consumer : public IConsumer<T> {
public:
    explicit Consumer(std::shared_ptr<Queue<T, size>> pQueue);

    Consumer() = default;
    ~Consumer();

    Consumer(const Consumer& other) = delete;
    Consumer& operator=(const Consumer& other) = delete;

    // WARNING: This class is NOT movable after using method Run()
    Consumer(Consumer&& other) noexcept = default;
    Consumer& operator=(Consumer&& other) noexcept;

    void Run() override;

private:
    inline static std::mutex queueMutex_{};
    inline static std::mutex ostreamMutex_{};

    std::shared_ptr<Queue<T, size>> pQueue_{};
    std::thread thread_{};
    std::size_t noSortedElements_{};

    void SortElement() override;
    T TakeFromQueue() override;
    double CalculateMean(const T& element);
};
} // namespace DataFlow

#include "impl/Consumer.tpp"

#endif // PRODUCERCONSUMERTHREADS_CONSUMER_HPP
