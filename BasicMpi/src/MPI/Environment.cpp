#include "MPI/Environment.hpp"
#include "mpi.h"

namespace MPI {
Environment::Environment(int& argc, char**& argv) {
    Init(argc, argv);
}

Environment::~Environment() {
    MPI_Finalize();
}

int Environment::GetSize() const {
    return size_;
}

void Environment::Init(int& argc, char**& argv) {
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_);
}
} // namespace MPI