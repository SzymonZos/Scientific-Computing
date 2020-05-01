#ifndef SCIENTIFICCOMPUTING_COMMUNICATOR_HPP
#define SCIENTIFICCOMPUTING_COMMUNICATOR_HPP

#include "MPI/Datatype.hpp"
#include "mpi.h"

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
    void Send(int dest, int tag, const T& value) const {
        Comm::Send(&value, 1, Map<T>::type, dest, tag);
    }

private:
    int rank_{};

    void Init();
    [[nodiscard]] Comm& Clone() const override;
};
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_COMMUNICATOR_HPP
