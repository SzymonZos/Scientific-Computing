#include "Timer.hpp"
#include <Dataflow>
#include <array>
#include <memory>

int main() {
    Timer timer;
    constexpr std::size_t noRandomNumbers = 10;
    constexpr std::size_t noConsumers = 4;
    constexpr std::size_t queueSize = 20;
    constexpr std::size_t noElements = 30;
    using Element = std::array<std::int32_t, noRandomNumbers>;

    auto queue = std::make_shared<DataFlow::Queue<Element, queueSize>>();

    DataFlow::Producer<Element, queueSize> producer{noElements, queue};
    producer.Run();

    std::array<DataFlow::Consumer<Element, queueSize>, noConsumers> consumers;
    for (auto& consumer : consumers) {
        consumer = DataFlow::Consumer{queue};
        consumer.Run();
    }

    return 0;
}
