#include "dataflow/Queue.hpp"

template<class T>
std::ostream& operator<<(std::ostream& stream, const DataFlow::Queue<T>& queue) {
    stream << "[";
    for (const auto& value : queue.queue_.front()) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}