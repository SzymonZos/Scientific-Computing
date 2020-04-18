#include "Timer.hpp"
#include "utils/Constants.hpp"
#include <Dataflow>
#include <array>
#include <cstdint>
#include <memory>
#include <vector>

using Element = std::array<std::int32_t, Constants::noRandomNumbers>;
using Queue = DataFlow::Queue<Element, Constants::queueSize>;
using Producer = DataFlow::Producer<Element, Constants::queueSize>;
using Consumer = DataFlow::Consumer<Element, Constants::queueSize>;

void Demo(const std::shared_ptr<Queue>& queue) {
    std::ofstream test{"logs/test.txt", std::ios::app};
    Timer timer{test};
    Producer producer{Constants::noElements, queue};
    producer.Run();
    std::array<Consumer, Constants::noConsumers> consumers{};
    std::for_each(consumers.begin(), consumers.end(), [=](auto& consumer) {
        consumer = DataFlow::Consumer{queue};
        consumer.Run();
    });
}

int main() {
    Timer timer{Ostream::file, "logs/timer.txt"};
    auto queue = std::make_shared<Queue>();
    Demo(queue);
    return 0;
}
