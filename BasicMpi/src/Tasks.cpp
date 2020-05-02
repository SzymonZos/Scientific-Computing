#include "Tasks.hpp"
#include "Mpi.hpp"

static void PointToPoint() {
    MPI::Communicator communicator{};
    std::size_t number = 2, max = 100;
    const auto rank = static_cast<std::size_t>(communicator.GetRank());
    const auto size = static_cast<std::size_t>(communicator.GetSize() - 1);
    if (rank) {
        for (std::size_t i = rank; i <= max; i += size) {
            communicator.Send(0, i);
        }
    } else {
        for (std::size_t i = 0; i < max; i++) {
            communicator.Recv(MPI_ANY_SOURCE, number);
            std::cout << number << '\n';
        }
    }
}

static void NonBlocking() {
    MPI::Communicator communicator{};
}

void Demo() {
    PointToPoint();
    NonBlocking();
}

void CheckNoPrimes(std::size_t maxNumber) {
    //
}