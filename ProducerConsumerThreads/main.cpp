#include <Dataflow>
#include <array>
#include <csignal>
#include <cstdlib>
#include <execinfo.h>
#include <memory>
#include <unistd.h>

void handler(int sig) {
    void* arrayDebug[10];
    int size = backtrace(arrayDebug, 10);
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(arrayDebug, size, STDERR_FILENO);
    exit(1);
}

int main() {
    signal(SIGSEGV, handler);
    constexpr std::size_t noRandomNumbers = 10000;
    constexpr std::size_t noConsumers = 4;
    constexpr std::size_t queueSize = 20;
    using Element = std::array<double, noRandomNumbers>;
    using Queue = DataFlow::Queue<Element, queueSize>;

    auto queue = std::make_shared<Queue>();

    DataFlow::Producer<Element, queueSize> producer{12, queue};
    producer.Run();

    std::array<DataFlow::Consumer<Element, queueSize>, noConsumers> consumers;
    for (auto& consumer : consumers) {
        consumer = DataFlow::Consumer{queue};
        consumer.Run();
    }

    return 0;
}
