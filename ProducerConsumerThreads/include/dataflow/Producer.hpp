#ifndef PRODUCERCONSUMERTHREADS_PRODUCER_HPP
#define PRODUCERCONSUMERTHREADS_PRODUCER_HPP

#include "interfaces/IProducer.hpp"

namespace DataFlow {
    template<class T>
    class Producer : public IProducer<T> {
    public:
        explicit Producer(uint32_t noElements);

        Producer() = delete;
        ~Producer() override = default;

        Producer(const Producer& other) = delete;
        Producer& operator=(const Producer& other) = delete;

        Producer(Producer&& other) = delete;
        Producer& operator=(Producer&& other) = delete;

        void GenerateRandomNumbers() override;
        void InsertIntoQueue(std::queue<T>& queue) override;

    private:
        static const uint32_t noRandomNumbers = 100000;
        T element_;
        uint32_t noElements_;
    };
}

#endif //PRODUCERCONSUMERTHREADS_PRODUCER_HPP
