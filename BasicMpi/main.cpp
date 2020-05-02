#include "Mpi.hpp"
#include "utils/Primes.hpp"
#include <cmath>
#include <iostream>

int main(int argc, char* argv[]) {
    MPI::Environment environment(argc, argv);
    MPI::Communicator communicator;
    int number;
    if (communicator.GetRank() == 0) {
        number = 2;
        for (int i = 1; i < environment.GetSize(); i++) {
            communicator.Send(i, 0, number);
        }
    } else {
        communicator.Recv(0, 0, number);
        std::cout << number << "^" << communicator.GetRank() << " = "
                  << std::pow(number, communicator.GetRank()) << std::endl;
    }
    return 0;
}