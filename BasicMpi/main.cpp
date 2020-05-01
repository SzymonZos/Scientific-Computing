#include "Mpi.hpp"
#include <cmath>
#include <iostream>

bool IsPrime(std::size_t number) {
    if (number < 4) {
        return number > 1;
    }
    if (!(number % 2) || !(number % 3)) {
        return false;
    }
    for (std::size_t i = 5; i * i <= number; i += 6) {
        if (!(number % i) || !(number % (i + 2))) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    MPI::Environment environment(argc, argv);
    int rank{};
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI::Communicator communicator;

    int number;
    if (!rank) {
        number = 2;
        for (int i = 1; i < environment.GetSize(); i++) {
            communicator.Send(i, 0, number);
        }
    } else {
        MPI_Recv(&number,
                 1,
                 MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD,
                 MPI_STATUSES_IGNORE);
        std::cout << number << "^" << rank << " = " << std::pow(number, rank)
                  << std::endl;
    }
    return 0;
}