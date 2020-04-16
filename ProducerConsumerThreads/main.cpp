#include <Dataflow>
#include <array>
#include <csignal>
#include <cstdlib>
#include <execinfo.h>
#include <memory>
#include <unistd.h>

void handler(int sig) {
    void* arrayDebug[20];
    int size = backtrace(arrayDebug, 20);
    std::cerr << "Error - signal: " << sig << "\n";
    backtrace_symbols_fd(arrayDebug, size, STDERR_FILENO);
    exit(1);
}

int main() {
    signal(SIGSEGV, handler);
    constexpr std::size_t noRandomNumbers = 10;
    constexpr std::size_t noConsumers = 4;
    constexpr std::size_t queueSize = 20;
    constexpr std::size_t noElements = 30;
    using Element = std::array<double, noRandomNumbers>;

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
