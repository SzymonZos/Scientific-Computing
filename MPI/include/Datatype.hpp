#ifndef SCIENTIFICCOMPUTING_MPI_DATATYPE_HPP
#define SCIENTIFICCOMPUTING_MPI_DATATYPE_HPP

#include "mpi.h"

namespace MPI {
template<typename T>
struct Map {
    static MPI_Datatype type;
};

template<typename T>
inline MPI_Datatype Map_t = Map<T>::type;
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_MPI_DATATYPE_HPP
