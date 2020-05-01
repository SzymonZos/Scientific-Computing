#include "MPI/Datatype.hpp"

namespace MPI {
template<typename T>
MPI_Datatype Map<T>::type = MPI_DATATYPE_NULL;

template<>
MPI_Datatype Map<unsigned char>::type = MPI_BYTE;

template<>
MPI_Datatype Map<char>::type = MPI_CHAR;

template<>
MPI_Datatype Map<short>::type = MPI_SHORT;

template<>
MPI_Datatype Map<int>::type = MPI_INT;

template<>
MPI_Datatype Map<long>::type = MPI_LONG;

template<>
MPI_Datatype Map<float>::type = MPI_FLOAT;

template<>
MPI_Datatype Map<double>::type = MPI_DOUBLE;

template<>
MPI_Datatype Map<long double>::type = MPI_LONG_DOUBLE;

template<>
MPI_Datatype Map<signed char>::type = MPI_SIGNED_CHAR;

template<>
MPI_Datatype Map<unsigned short>::type = MPI_UNSIGNED_SHORT;

template<>
MPI_Datatype Map<unsigned long>::type = MPI_UNSIGNED_LONG;

template<>
MPI_Datatype Map<unsigned>::type = MPI_UNSIGNED;
} // namespace MPI