#include "Communicator.hpp"

namespace MPI {
Communicator::Communicator() :
    Comm{MPI_COMM_WORLD},
    rank_{Comm::Get_rank()},
    size_{Comm::Get_size()} {}

Communicator::~Communicator() {
    Communicator::Barrier();
}

int Communicator::GetRank() const {
    return rank_;
}

int Communicator::GetSize() const {
    return size_;
}

void Communicator::Barrier() const {
    Comm::Barrier();
}

Comm& Communicator::Clone() const {
    return *static_cast<Comm*>(const_cast<Communicator*>(this));
}
} // namespace MPI