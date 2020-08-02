#ifndef SCIENTIFICCOMPUTING_MPI_COMMUNICATOR_TPP
#define SCIENTIFICCOMPUTING_MPI_COMMUNICATOR_TPP

namespace MPI {
template<typename T>
void Communicator::Send(int dest, const T& value, int tag) const {
    Comm::Send(&value, 1, Map_t<T>, dest, tag);
}

template<typename T>
void Communicator::Send(int dest, gsl::span<const T> array, int tag) const {
    Comm::Send(&array.front(), array.size(), Map_t<T>, dest, tag);
}

template<typename T, std::size_t size>
void Communicator::Send(int dest,
                        const std::array<T, size>& array,
                        int tag) const {
    Comm::Send(&array.front(), size, Map_t<T>, dest, tag);
}

template<typename T>
Status Communicator::Recv(int source, T& value, int tag) const {
    Status status;
    Comm::Recv(&value, 1, Map_t<T>, source, tag, status);
    return status;
}

template<typename T>
Status Communicator::Recv(int source, gsl::span<T> array, int tag) const {
    Status status;
    Comm::Recv(&array.front(), array.size(), Map_t<T>, source, tag, status);
    return status;
}

template<typename T, std::size_t size>
Status
Communicator::Recv(int source, std::array<T, size>& array, int tag) const {
    Status status;
    Comm::Recv(&array.front(), size, Map_t<T>, source, tag, status);
    return status;
}

template<typename T>
Request Communicator::ISend(int dest, const T& value, int tag) const {
    return Isend(&value, 1, Map_t<T>, dest, tag);
}

template<typename T>
Request
Communicator::ISend(int dest, gsl::span<const T> array, int tag) const {
    return Isend(&array.front(), array.size(), Map_t<T>, dest, tag);
}

template<typename T, std::size_t size>
Request Communicator::ISend(int dest,
                            const std::array<T, size>& array,
                            int tag) const {
    return Isend(&array.front(), size, Map_t<T>, dest, tag);
}

template<typename T>
Request Communicator::IRecv(int source, T& value, int tag) const {
    return Irecv(&value, 1, Map_t<T>, source, tag);
}

template<typename T>
Request Communicator::IRecv(int source, gsl::span<T> array, int tag) const {
    return Irecv(&array.front(), array.size(), Map_t<T>, source, tag);
}

template<typename T, std::size_t size>
Request
Communicator::IRecv(int source, std::array<T, size>& array, int tag) const {
    return Irecv(&array.front(), size, Map_t<T>, source, tag);
}

template<typename T>
T Communicator::Reduce(int root, const T& toSend, const Op& operation) const {
    T output;
    Comm::Reduce(&toSend, &output, 1, Map_t<T>, operation, root);
    return output;
}
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_MPI_COMMUNICATOR_TPP
