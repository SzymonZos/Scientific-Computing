#ifndef SCIENTIFICCOMPUTING_COMMUNICATOR_HPP
#define SCIENTIFICCOMPUTING_COMMUNICATOR_HPP

#include "MPI/Datatype.hpp"
#include "mpi.h"
#include <array>
#include <gsl/span>

namespace MPI {
class Communicator : private Comm {
public:
    Communicator();
    ~Communicator() override = default;

    Communicator(const Communicator& other) = delete;
    Communicator& operator=(const Communicator& other) = delete;

    Communicator(Communicator&& other) = delete;
    Communicator& operator=(Communicator&& other) = delete;

    [[nodiscard]] int GetRank() const;

    template<typename T>
    void Send(int dest, int tag, const T& value) const;

    template<typename T>
    void Send(int dest, int tag, gsl::span<const T> array) const;

    template<typename T, std::size_t size>
    void Send(int dest, int tag, const std::array<T, size>& array) const;

    template<typename T>
    Status Recv(int source, int tag, T& value) const;

    template<typename T>
    Status Recv(int source, int tag, gsl::span<T> array) const;

    template<typename T, std::size_t size>
    Status Recv(int source, int tag, std::array<T, size>& array) const;

private:
    int rank_{};

    void Init();
    [[nodiscard]] Comm& Clone() const override;
};
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_COMMUNICATOR_HPP
