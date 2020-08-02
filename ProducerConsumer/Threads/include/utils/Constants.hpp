#ifndef SCIENTIFICCOMPUTING_PRODUCERCONSUMERTHREADS_CONSTANTS_HPP
#define SCIENTIFICCOMPUTING_PRODUCERCONSUMERTHREADS_CONSTANTS_HPP

struct Constants {
    static constexpr std::size_t defaultQueueSize{100};
    static constexpr std::size_t noRandomNumbers{100'000};
    static constexpr std::size_t noConsumers{8};
    static constexpr std::size_t queueSize{200};
    static constexpr std::size_t noElements{4000};
};

#endif // SCIENTIFICCOMPUTING_PRODUCERCONSUMERTHREADS_CONSTANTS_HPP
