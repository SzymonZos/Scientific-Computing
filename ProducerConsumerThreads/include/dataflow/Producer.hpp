#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_HPP

#include "interfaces/IProducer.hpp"

namespace DataFlow {
    template<class T>
    class Producer : public IProducer<T> {
    public:
        explicit Producer(uint32_t numElements);

        Producer() = delete;
        ~Producer() override = default;

        Producer(const Producer& other) = delete;
        Producer& operator=(const Producer& other) = delete;

        Producer(Producer&& other) = delete;
        Producer& operator=(Producer&& other) = delete;

        void GenerateRandomNumbers(uint32_t count) override;
        void InsertIntoQueue(std::queue<T>& queue) override;

    private:
        T element_;
        uint32_t numElements_;
    };
}

#endif //PRODUCERCONSUMERTHREADS_PRODUCER_HPP
