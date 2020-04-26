#include "mpi.h"
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
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int number;
    if (!rank) {
        number = 2;
        for (int i = 1; i < size; i++) {
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
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
    MPI_Finalize();
    return 0;
}