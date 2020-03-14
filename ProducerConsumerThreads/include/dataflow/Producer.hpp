#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_HPP

#include "interfaces/IProducer.hpp"
#include <memory>
#include <thread>

namespace DataFlow {
    template<class T>
    class Producer : public IProducer<T> {
    public:
        explicit Producer(uint32_t noElements,
                          std::shared_ptr<Queue<T>> pQueue);

        Producer() = delete;
        ~Producer() override;

        Producer(const Producer& other) = delete;
        Producer& operator=(const Producer& other) = delete;

        Producer(Producer&& other) = delete;
        Producer& operator=(Producer&& other) = delete;

    private:
        static const int32_t minRandomNumber = -2048;
        static const int32_t maxRandomNumber = 2048;

        uint32_t noElements_;
        std::shared_ptr<Queue<T>> pQueue_;
        std::thread thread_;

        [[nodiscard]] int32_t GenerateRandomNumber() const override;
        [[nodiscard]] T FillContainer() const override;
        void InsertIntoQueue() override;
    };
}

#include "impl/Producer.tpp"

#endif //PRODUCERCONSUMERTHREADS_PRODUCER_HPP
