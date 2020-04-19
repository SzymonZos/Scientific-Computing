#ifndef PRODUCERCONSUMERTHREADS_OPERATORS_HPP
#define PRODUCERCONSUMERTHREADS_OPERATORS_HPP

#include <array>
#include <iostream>

namespace DataFlow {
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, std::array<T, N>& array) {
    stream << "[";
    for (const auto& value : array) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}

template<template<typename...> typename TT,
         typename... T,
         typename = std::enable_if_t<!std::is_same_v<TT<T...>, std::string>>>
std::ostream& operator<<(std::ostream& stream, const TT<T...>& collection) {
    stream << "[";
    for (const auto& value : collection) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}
} // namespace DataFlow
#endif // PRODUCERCONSUMERTHREADS_OPERATORS_HPP
