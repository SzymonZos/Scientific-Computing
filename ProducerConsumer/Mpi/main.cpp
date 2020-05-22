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
    return 0;
}