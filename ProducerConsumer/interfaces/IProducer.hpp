#ifndef PRODUCERCONSUMER_IPRODUCER_HPP
#define PRODUCERCONSUMER_IPRODUCER_HPP

template<class T>
class IProducer {
public:
    virtual ~IProducer() = default;

    [[nodiscard]] virtual T FillContainer() = 0;
    virtual void InsertIntoQueue() = 0;
    virtual void Run() = 0;
};

#endif // PRODUCERCONSUMER_IPRODUCER_HPP
