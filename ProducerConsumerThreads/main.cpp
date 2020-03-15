#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <Dataflow>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static const std::size_t noRandomNumbers = 100;
static const std::size_t noConsumers = 4;

typedef std::array<double, noRandomNumbers> array;

void handler(int sig) {
    void* array[10];
    size_t size;

    size = backtrace(array, 10);
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

int main() {
    signal(SIGSEGV, handler);
    auto queue = std::make_shared<DataFlow::Queue<array>>();

    DataFlow::Producer<array> producer{12, queue};
    producer.Run();

    std::array<DataFlow::Consumer<array>, noConsumers> consumers;
    for (auto& consumer : consumers) {
        consumer = DataFlow::Consumer{queue};
        consumer.Run();
    }


    return 0;
}
