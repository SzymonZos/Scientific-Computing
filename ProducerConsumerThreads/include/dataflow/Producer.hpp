#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_HPP

#include "interfaces/IProducer.hpp"
#include <memory>

namespace DataFlow {
    template<class T>
    class Producer : public IProducer<T> {
    public:
        explicit Producer(uint32_t noElements,
                          std::shared_ptr<Queue<T>> pQueue);

        Producer() = delete;
        ~Producer() override = default;

        Producer(const Producer& other) = delete;
        Producer& operator=(const Producer& other) = delete;

        Producer(Producer&& other) = delete;
        Producer& operator=(Producer&& other) = delete;

        int32_t GenerateRandomNumber() override;
        T FillContainer() override;

        void InsertIntoQueue() override;

    private:
        static const int32_t minRandomNumber = -2048;
        static const int32_t maxRandomNumber = 2048;

        uint32_t noElements_;
        std::shared_ptr<Queue<T>> pQueue_;
    };
}

#include "impl/Producer.tpp"

#endif //PRODUCERCONSUMERTHREADS_PRODUCER_HPP
