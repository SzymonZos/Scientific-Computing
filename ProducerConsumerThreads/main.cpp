#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include "utils/Operators.hpp"
#include <Dataflow>

static const uint32_t noRandomNumbers = 10;
typedef std::array<double, noRandomNumbers> array;

int main() {
    auto queue = std::make_shared<DataFlow::Queue<array>>();
//    std::vector<double> test = {1.0, 2.3, -1.5};
//    auto& someQueue = someQueueWrapper.GetQueue();
//    someQueue.push({1, 2, 3});
//    someQueue.push({4, 5, 3});
//    someQueue.push({6, 8, 9, 10});
//
//    std::cout << test << std::endl;
//    std::cout << someQueue.back() << std::endl;
//    std::cout << someQueueWrapper << std::endl;
//    someQueue.back();
//    someQueue.pop();
//    std::cout << someQueueWrapper << std::endl;
//
//    DataFlow::Queue<array> testQ;
//    auto& queue = testQ.GetQueue();
//    queue.push({0.2, 0.3, -0.4});
//    queue.push({2, 3, -0.4});
//
//    std::cout << testQ << std::endl;

    std::unique_ptr<DataFlow::IProducer<array>> producer;
    producer = std::make_unique<DataFlow::Producer<array>>(11, queue);
    producer->InsertIntoQueue();
    std::cout << *queue;

    return 0;
}
