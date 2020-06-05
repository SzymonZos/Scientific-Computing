#include "Consumer.hpp"
#include "Mpi.hpp"
#include "Producer.hpp"
#include <array>

using Element = std::array<std::int32_t, 100'000>;
using Producer = MPI::Producer<Element>;
using Consumer = MPI::Consumer<Element>;
using Communicator = MPI::CommonCommunicator<Element>;

int main(int argc, char* argv[]) {
    MPI::Environment environment{argc, argv};
    Communicator communicator{};
    Consumer consumer{communicator};
    Producer producer{4000, communicator};
    const auto rank = communicator.GetRank<std::size_t>();
    if (rank) {
        consumer.Run();
    } else {
        producer.Run();
    }
    auto sum = communicator.Reduce(0, consumer.GetNoSortedElements(), MPI_SUM);
    if (!rank) {
        std::cout << "Sorted all: " << sum << '\n';
    }
    return 0;
}