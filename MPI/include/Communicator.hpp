#ifndef SCIENTIFICCOMPUTING_COMMUNICATOR_HPP
#define SCIENTIFICCOMPUTING_COMMUNICATOR_HPP

#include "Datatype.hpp"
#include "mpi.h"
#include <array>
#include <gsl/span>

namespace MPI {
class Communicator : private Comm {
public:
    Communicator();
    ~Communicator() override;

    Communicator(const Communicator& other) = delete;
    Communicator& operator=(const Communicator& other) = delete;

    Communicator(Communicator&& other) = delete;
    Communicator& operator=(Communicator&& other) = delete;

    [[nodiscard]] int GetRank() const;
    [[nodiscard]] int GetSize() const;
    void Barrier() const override;

    template<typename T>
    void Send(int dest, const T& value, int tag = 0) const;

    template<typename T>
    void Send(int dest, gsl::span<const T> array, int tag = 0) const;

    template<typename T, std::size_t size>
    void Send(int dest, const std::array<T, size>& array, int tag = 0) const;

    template<typename T>
    Status Recv(int source, T& value, int tag = 0) const;

    template<typename T>
    Status Recv(int source, gsl::span<T> array, int tag = 0) const;

    template<typename T, std::size_t size>
    Status Recv(int source, std::array<T, size>& array, int tag = 0) const;

    template<typename T>
    Request ISend(int dest, const T& value, int tag = 0) const;

    template<typename T>
    Request ISend(int dest, gsl::span<const T> array, int tag = 0) const;

    template<typename T, std::size_t size>
    Request
    ISend(int dest, const std::array<T, size>& array, int tag = 0) const;

    template<typename T>
    Request IRecv(int source, T& value, int tag = 0) const;

    template<typename T>
    Request IRecv(int source, gsl::span<T> array, int tag = 0) const;

    template<typename T, std::size_t size>
    Request IRecv(int source, std::array<T, size>& array, int tag = 0) const;

    template<typename T>
    T Reduce(int root, const T& toSend, const Op& operation) const;

private:
    int rank_{};
    int size_{};

    [[nodiscard]] Comm& Clone() const override;
};
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_COMMUNICATOR_HPP
