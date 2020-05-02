#ifndef SCIENTIFICCOMPUTING_COMMUNICATORIMPL_HPP
#define SCIENTIFICCOMPUTING_COMMUNICATORIMPL_HPP

namespace MPI {
template<typename T>
void Communicator::Send(int dest, int tag, const T& value) const {
    Comm::Send(&value, 1, Map_t<T>, dest, tag);
}

template<typename T>
void Communicator::Send(int dest, int tag, gsl::span<const T> array) const {
    Comm::Send(&array.front(), array.size(), Map_t<T>, dest, tag);
}

template<typename T, std::size_t size>
void Communicator::Send(int dest,
                        int tag,
                        const std::array<T, size>& array) const {
    Comm::Send(&array.front(), size, Map_t<T>, dest, tag);
}

template<typename T>
Status Communicator::Recv(int source, int tag, T& value) const {
    Status status;
    Comm::Recv(&value, 1, Map_t<T>, source, tag, status);
    return status;
}

template<typename T>
Status Communicator::Recv(int source, int tag, gsl::span<T> array) const {
    Status status;
    Comm::Recv(&array.front(), array.size(), Map_t<T>, source, tag, status);
    return status;
}

template<typename T, std::size_t size>
Status
Communicator::Recv(int source, int tag, std::array<T, size>& array) const {
    MPI_Status status;
    Comm::Recv(&array.front(), size, Map_t<T>, source, tag, status);
    return status;
}
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_COMMUNICATORIMPL_HPP
