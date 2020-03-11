#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include "utils/Operators.hpp"
#include "dataflow/Queue.hpp"

template<class T>
class Queue {
private:
    std::queue<T> queue_;

public:
    std::queue<T>& GetQueue() {
        return queue_;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Queue& queue) {
        stream << "[";
        for (const auto& value : queue.queue_.front()) {
            stream << value << ", ";
        }
        stream << "\b\b]";
        return stream;
    }
};


int main() {
    Queue<std::array<double, 10>> someQueueWrapper;
    std::vector<double> test = {1.0, 2.3, -1.5};
    auto& someQueue = someQueueWrapper.GetQueue();
    someQueue.push({1, 2, 3});
    someQueue.push({4, 5, 3});
    someQueue.push({6, 8, 9, 10});

//    std::cout << test << std::endl;
    std::cout << someQueue.back() << std::endl;
    std::cout << someQueueWrapper << std::endl;
    someQueue.back();
    someQueue.pop();
    std::cout << someQueueWrapper << std::endl;

    DataFlow::Queue<std::array<double, 10>> testQ;
    auto& queue = testQ.GetQueue();
    queue.push({0.2, 0.3, -0.4});
    queue.push({2, 3, -0.4});

    std::cout << testQ << std::endl;

    return 0;
}
