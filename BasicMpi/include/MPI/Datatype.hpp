#ifndef SCIENTIFICCOMPUTING_DATATYPE_HPP
#define SCIENTIFICCOMPUTING_DATATYPE_HPP

// I don't know less hacky way :(

#include "mpi.h"

namespace MPI {
template<typename T>
struct Map {
    static MPI_Datatype type;
};
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_DATATYPE_HPP
