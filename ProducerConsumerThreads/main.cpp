#include "Timer.hpp"
#include "utils/Constants.hpp"
#include "Dataflow.hpp"
#include <array>
#include <cstdint>
#include <memory>
#include <vector>

using Element = std::array<std::int32_t, Constants::noRandomNumbers>;
using Queue = DataFlow::Queue<Element, Constants::queueSize>;
using Producer = DataFlow::Producer<Element, Constants::queueSize>;
using Consumer = DataFlow::Consumer<Element, Constants::queueSize>;

void RunComparison(const std::shared_ptr<Queue>& queue,
                   const std::size_t noIterations) {
    std::ofstream comparisonFile{PROJECT_SOURCE_DIR "/logs/comparison.txt",
                                 std::ios::app};
    comparisonFile << "Build info: " BUILD_INFO "\n";
    std::vector<std::size_t> noConsumers(noIterations);
    std::iota(noConsumers.begin(), noConsumers.end(), 1);
    std::for_each(noConsumers.begin(), noConsumers.end(), [&](auto iteration) {
        comparisonFile << std::to_string(iteration) << ": ";
        Timer timer{comparisonFile};
        Producer producer{Constants::noElements, queue};
        producer.Run();
        std::vector<Consumer> consumers(iteration);
        std::for_each(consumers.begin(), consumers.end(), [=](auto& consumer) {
            consumer = DataFlow::Consumer{queue};
            consumer.Run();
        });
    });
    comparisonFile << '\n';
}

void RunDemo(const std::shared_ptr<Queue>& queue) {
    std::ofstream test{"logs/demo.txt", std::ios::app};
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
    Timer timer{};
    auto queue = std::make_shared<Queue>();
    // RunDemo(queue);
    RunComparison(queue, 20);
    return 0;
}
