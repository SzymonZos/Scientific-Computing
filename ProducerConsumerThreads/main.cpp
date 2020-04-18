#include "Timer.hpp"
#include <Dataflow>
#include <array>
#include <cstdint>
#include <memory>

int main() {
    constexpr std::size_t noRandomNumbers = 100'000;
    constexpr std::size_t noConsumers = 8;
    constexpr std::size_t queueSize = 200;
    constexpr std::size_t noElements = 4000;
    using Element = std::array<std::int32_t, noRandomNumbers>;

    Timer timer;
    auto queue = std::make_shared<DataFlow::Queue<Element, queueSize>>();
    DataFlow::Producer<Element, queueSize> producer{noElements, queue};
    producer.Run();
    std::array<DataFlow::Consumer<Element, queueSize>, noConsumers> consumers;
    std::for_each(consumers.begin(), consumers.end(), [=](auto& consumer) {
        consumer = DataFlow::Consumer{queue};
        consumer.Run();
    });
    return 0;
}
