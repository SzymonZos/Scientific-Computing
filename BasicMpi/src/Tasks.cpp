#include "Tasks.hpp"
#include "Mpi.hpp"
#include "Timer.hpp"
#include "utils/Primes.hpp"

static void PointToPoint() {
    MPI::Communicator communicator{};
    std::size_t number{2}, max{100};
    const auto rank = static_cast<std::size_t>(communicator.GetRank());
    const auto size = static_cast<std::size_t>(communicator.GetSize() - 1);
    if (rank) {
        for (std::size_t i = rank; i <= max; i += size) {
            communicator.Send(0, i * i);
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
    std::size_t number = 2, max = 100;
    const auto rank = static_cast<std::size_t>(communicator.GetRank());
    const auto size = static_cast<std::size_t>(communicator.GetSize() - 1);
    if (rank) {
        for (std::size_t i = rank; i <= max; i += size) {
            communicator.ISend(0, i * number);
        }
    } else {
        for (std::size_t i = 0; i < max; i++) {
            MPI::Request recv{communicator.IRecv(MPI_ANY_SOURCE, number)};
            // recv.Wait();
            std::cout << std::boolalpha << "Test: " << recv.Test()
                      << " got: " << number << '\n';
        }
    }
}

void Demo() {
    PointToPoint();
    NonBlocking();
}

void CheckNoPrimes(std::size_t maxNumber) {
    MPI::Communicator communicator{};
    std::size_t noPrimes{};
    bool isPrime{};
    const auto rank = static_cast<std::size_t>(communicator.GetRank());
    const auto size = static_cast<std::size_t>(communicator.GetSize() - 1);
    if (rank) {
        for (std::size_t i = rank; i <= maxNumber; i += size) {
            communicator.Send(0, IsPrime(i));
        }
    } else {
        Timer timer;
        for (std::size_t i = 0; i < maxNumber; i++) {
            communicator.Recv(MPI_ANY_SOURCE, isPrime);
            noPrimes += isPrime;
        }
        std::cout << noPrimes << '\n';
    }
}