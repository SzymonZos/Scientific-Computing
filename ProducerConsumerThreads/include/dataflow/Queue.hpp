#ifndef PRODUCERCONSUMERTHREADS_QUEUE_HPP
#define PRODUCERCONSUMERTHREADS_QUEUE_HPP

#include "forward/queue_fwd.hpp"
#include <mutex>
#include <ostream>
#include <queue>

namespace DataFlow {
template<class T, std::size_t size = 100>
class Queue {
public:
    bool isProducerDone = false;

    typedef typename std::queue<T>::value_type value_type;
    typedef typename std::queue<T>::reference reference;
    typedef typename std::queue<T>::const_reference const_reference;
    typedef typename std::queue<T>::size_type size_type;

    Queue() = default;
    ~Queue() = default;

    Queue(const Queue& other) = delete;
    Queue& operator=(const Queue& other) = delete;

    Queue(Queue&& other) = delete;
    Queue& operator=(Queue&& other) = delete;

    [[nodiscard]] bool IsEmpty() const;
    size_type Size() const;

    reference Front();
    const_reference Front() const;

    reference Back();
    const_reference Back() const;

    void Push(const value_type& value);
    void Push(value_type&& value);

    template<typename... Args>
    decltype(auto) Emplace(Args... args);

    void Pop();

    friend std::ostream& operator<<<>(std::ostream& stream,
                                      const Queue<T>& queue);

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::size_t noElements_ = 0;
};
} // namespace DataFlow

#include "impl/Queue.tpp"

#endif // PRODUCERCONSUMERTHREADS_QUEUE_HPP
