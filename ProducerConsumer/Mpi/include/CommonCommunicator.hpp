#ifndef SCIENTIFICCOMPUTING_COMMONCOMMUNICATOR_HPP
#define SCIENTIFICCOMPUTING_COMMONCOMMUNICATOR_HPP

#include "Communicator.hpp"

namespace MPI {
template<typename T>
using ValueType = typename T::value_type;

template<class T>
class CommonCommunicator : public Communicator {
public:
    ~CommonCommunicator() override = default;

    template<typename Type>
    Type GetSize();

    template<typename Type>
    Type GetRank();

    ValueType<T> GetLimit();
    bool IsLastMsg(const T& msg);

private:
    ValueType<T> limit_{std::numeric_limits<ValueType<T>>::max()};
    T lastMsg_{limit_};
};

} // namespace MPI

#include "impl/CommonCommunicator.tpp"

#endif // SCIENTIFICCOMPUTING_COMMONCOMMUNICATOR_HPP
