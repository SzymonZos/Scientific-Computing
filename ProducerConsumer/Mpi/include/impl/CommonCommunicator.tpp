#ifndef SCIENTIFICCOMPUTING_COMMONCOMMUNICATOR_TPP
#define SCIENTIFICCOMPUTING_COMMONCOMMUNICATOR_TPP

#include <CommonCommunicator.hpp>

namespace MPI {
template<class T>
template<typename Type>
Type CommonCommunicator<T>::GetSize() {
    return static_cast<Type>(Communicator::GetSize());
}

template<class T>
template<typename Type>
Type CommonCommunicator<T>::GetRank() {
    return static_cast<Type>(Communicator::GetRank());
}

template<class T>
ValueType<T> CommonCommunicator<T>::GetLimit() {
    return limit_;
}

template<class T>
bool CommonCommunicator<T>::IsLastMsg(const T& msg) {
    return msg[0] == limit_;
}

} // namespace MPI

#endif // SCIENTIFICCOMPUTING_COMMONCOMMUNICATOR_TPP
