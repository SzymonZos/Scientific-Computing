#ifndef PRODUCERCONSUMER_ICONSUMER_HPP
#define PRODUCERCONSUMER_ICONSUMER_HPP

template<class T>
class IConsumer {
public:
    virtual ~IConsumer() = default;

    virtual void SortElement() = 0;
    [[nodiscard]] virtual T TakeFromQueue() = 0;
    [[nodiscard]] virtual double CalculateMean(const T& element) = 0;
    virtual void Run() = 0;
};

#endif // PRODUCERCONSUMER_ICONSUMER_HPP
