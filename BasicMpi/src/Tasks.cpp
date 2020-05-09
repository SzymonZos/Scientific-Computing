#include "Tasks.hpp"
#include "Mpi.hpp"
#include "Timer.hpp"
#include "utils/Primes.hpp"
#include <cmath>

static void Basic() {
    MPI::Communicator communicator;
    int number;
    switch (communicator.GetRank()) {
    case 0:
        number = 2;
        for (int i = 1; i < communicator.GetSize(); i++) {
            communicator.Send(i, number);
        }
        break;
    default:
        communicator.Recv(0, number);
        std::cout << number << "^" << communicator.GetRank() << " = "
                  << std::pow(number, communicator.GetRank()) << std::endl;
        break;
    }
}

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
            std::cout << std::boolalpha << "Test: " << recv.Test()
                      << " got: " << number << '\n';
        }
    }
}

void Demo() {
    Basic();
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

void CheckNoPrimesPlain(std::size_t maxNumber) {
    Timer timer;
    MPI::Communicator communicator{};
    std::size_t noPrimes{};
    const auto rank = static_cast<std::size_t>(communicator.GetRank());
    const auto size = static_cast<std::size_t>(communicator.GetSize());
    for (std::size_t i = rank; i <= maxNumber; i += size) {
        noPrimes += IsPrime(i);
    }
    auto sum = communicator.Reduce(0, noPrimes, MPI_SUM);
    if (!rank) {
        std::cout << sum << '\n';
    }
}

void CheckNoPrimesMsgs(std::size_t maxNumber) {
    MPI::Communicator communicator{};
    std::size_t noPrimes{}, number{}, destination{};
    const auto rank = static_cast<std::size_t>(communicator.GetRank());
    const auto size = static_cast<std::size_t>(communicator.GetSize() - 1);
    const auto limit = std::numeric_limits<std::size_t>::max();
    if (rank) {
        while (true) {
            MPI::Request recv{communicator.IRecv(0, number)};
            recv.Wait();
            if (number == limit) {
                break;
            }
            noPrimes += IsPrime(number);
            communicator.ISend(0, rank);
        }
    } else {
        Timer timer{};
        for (std::size_t i = 0; i <= maxNumber; i++) {
            if (i < size) {
                communicator.ISend(static_cast<int>(i + 1), i);
            } else {
                MPI::Request recv{
                    communicator.IRecv(MPI_ANY_SOURCE, destination)};
                recv.Wait();
                communicator.ISend(static_cast<int>(destination), i);
            }
        }
        for (std::size_t i = 1; i <= size; i++) {
            communicator.ISend(i, limit);
        }
    }
    auto sum = communicator.Reduce(0, noPrimes, MPI_SUM);
    if (!communicator.GetRank()) {
        std::cout << sum << '\n';
    }
}