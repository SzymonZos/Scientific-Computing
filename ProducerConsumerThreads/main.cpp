#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include "utils/Operators.hpp"
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

//    std::unique_ptr<DataFlow::IProducer<array>> producer;

//    std::array<DataFlow::Producer<array>, noConsumers> producers;
    std::vector<DataFlow::Producer<array>> producers;
//    producers.reserve(4);
//    producers.emplace_back(11, queue);
//    producers.emplace_back(11, queue);
//    producers.emplace_back(11, queue);
    producers.emplace_back(11, queue);
//    producers.emplace_back();
//    producers.emplace_back();
//    producers.emplace_back();
//    producers.emplace_back();
//    producers.emplace_back();



//    std::unique_ptr<DataFlow::IConsumer<array>> consumer;
//    consumer = std::make_unique<DataFlow::Consumer<array>>(queue);

//    std::vector<DataFlow::Consumer<array>> consumers;
//    consumers.reserve(4);
//    consumers.emplace_back(queue);
//    consumers.emplace_back(queue);
//    consumers.emplace_back(queue);
//    consumers.emplace_back(queue);
//    consumers.emplace_back(queue);




    return 0;
}
