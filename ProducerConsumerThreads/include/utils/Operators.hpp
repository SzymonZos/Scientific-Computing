#ifndef PRODUCERCONSUMERTHREADS_OPERATORS_HPP
#define PRODUCERCONSUMERTHREADS_OPERATORS_HPP

#include <iostream>
#include <array>

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const std::array<T, N>& array) {
    stream << "[";
    for (const auto& value : array) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}

template<template<typename...> typename TT, typename... T>
std::ostream& operator<<(std::ostream& stream, const TT<T...>& collection) {
    stream << "[";
    for (const auto& value : collection) {
        stream << value << ", ";
    }
    stream << "\b\b]";
    return stream;
}

#endif //PRODUCERCONSUMERTHREADS_OPERATORS_HPP
