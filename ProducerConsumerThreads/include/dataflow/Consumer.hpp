#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_HPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_HPP

#include "interfaces/IConsumer.hpp"

namespace DataFlow {
    template<class T>
    class Consumer : public IConsumer<T> {
    public:
        explicit Consumer(std::shared_ptr<Queue<T>> pQueue);

        Consumer() = delete;
        ~Consumer();

        Consumer(const Consumer& other) = delete;
        Consumer& operator=(const Consumer& other) = delete;

        Consumer(Consumer&& other) = delete;
        Consumer& operator=(Consumer&& other) = delete;

        T SortElement() override;
        void TakeFromQueue() override;

    private:
        std::shared_ptr<Queue<T>> pQueue_;
        std::thread thread_;
    };
}

#include "impl/Consumer.tpp"

#endif //PRODUCERCONSUMERTHREADS_CONSUMER_HPP
