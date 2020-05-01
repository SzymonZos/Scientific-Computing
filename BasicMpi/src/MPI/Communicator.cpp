#include "MPI/Communicator.hpp"

namespace MPI {
Communicator::Communicator() : Comm{MPI_COMM_WORLD} {
    Init();
}

int Communicator::GetRank() const {
    return rank_;
}

void Communicator::Init() {
    rank_ = Get_rank();
}

Comm& Communicator::Clone() const {}
} // namespace MPI