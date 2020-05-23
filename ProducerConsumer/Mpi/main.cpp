#include "Consumer.hpp"
#include "Mpi.hpp"
#include "Producer.hpp"
#include <array>

using Element = std::array<std::int32_t, 1000>;
using Producer = MPI::Producer<Element>;
using Consumer = MPI::Consumer<Element>;

int main(int argc, char* argv[]) {
    MPI::Environment environment{argc, argv};
    MPI::Communicator communicator{};
    Consumer consumer{};
    Producer producer{100};
    if (communicator.GetRank()) {
        consumer.Run();
    } else {
        producer.Run();
    }
    auto sum = communicator.Reduce(0, consumer.GetNoSortedElements(), MPI_SUM);
    if (!communicator.GetRank()) {
        std::cout << "Sorted all: " << sum << '\n';
    }
    return 0;
}