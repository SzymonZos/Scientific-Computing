#include "Mpi.hpp"
#include "Tasks.hpp"
#include <cmath>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI::Environment environment{argc, argv};
    MPI::Communicator communicator;
    int number;
    switch (communicator.GetRank()) {
    case 0:
        number = 2;
        for (int i = 1; i < environment.GetSize(); i++) {
            communicator.Send(i, number);
        }
        break;
    default:
        communicator.Recv(0, number);
        std::cout << number << "^" << communicator.GetRank() << " = "
                  << std::pow(number, communicator.GetRank()) << std::endl;
        break;
    }
    communicator.Barrier();
    Demo();
    CheckNoPrimes(10'000'000);
    CheckNoPrimesPlain(10'000'000);
    CheckNoPrimesMultipleRecvs(100'000);
    return 0;
}