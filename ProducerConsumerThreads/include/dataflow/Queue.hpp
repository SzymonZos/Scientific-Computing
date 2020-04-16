#ifndef PRODUCERCONSUMERTHREADS_QUEUE_HPP
#define PRODUCERCONSUMERTHREADS_QUEUE_HPP

#include "forward/queue_fwd.hpp"
#include "utils/Constants.hpp"
#include <mutex>
#include <ostream>
#include <queue>

namespace DataFlow {

template<typename T>
using value_type = typename std::queue<T>::value_type;

template<typename T>
using reference = typename std::queue<T>::reference;

template<typename T>
using const_reference = typename std::queue<T>::const_reference;

template<typename T>
using size_type = typename std::queue<T>::size_type;

template<class T, std::size_t size = Constants::defaultQueueSize>
class Queue {
public:
    bool isProducerDone_ = false;

    Queue() = default;
    ~Queue() = default;

    Queue(const Queue& other) = delete;
    Queue& operator=(const Queue& other) = delete;

    Queue(Queue&& other) = delete;
    Queue& operator=(Queue&& other) = delete;

    [[nodiscard]] bool IsEmpty() const;
    size_type<T> Size() const;

    reference<T> Front();
    const_reference<T> Front() const;

    reference<T> Back();
    const_reference<T> Back() const;

    void Push(const value_type<T>& value);
    void Push(value_type<T>&& value);

    template<typename... Args>
    decltype(auto) Emplace(Args... args);

    void Pop();

    friend std::ostream& operator<<<>(std::ostream& stream,
                                      const Queue<T>& queue);

private:
    std::queue<T> queue_;
    mutable std::mutex elementMutex_{};
    std::size_t noElements_ = 0;
};
} // namespace DataFlow

#include "impl/Queue.tpp"

#endif // PRODUCERCONSUMERTHREADS_QUEUE_HPP
