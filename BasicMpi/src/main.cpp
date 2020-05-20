#include "Mpi.hpp"
#include "Tasks.hpp"
#include <array>
#include <functional>

int main(int argc, char* argv[]) {
    using PrimeChecker = std::function<void(std::size_t)>;
    MPI::Environment environment{argc, argv};
    Demo();
    std::size_t base = 1'000'000;
    std::array<std::size_t, 3> numbers{base, 10 * base, 100 * base};
    std::array<PrimeChecker, 2> primeCheckers{CheckNoPrimesPlain,
                                              CheckNoPrimesMsgs};
    for (const auto& number : numbers) {
        for (const auto& primeChecker : primeCheckers) {
            primeChecker(number);
        }
    }
    return 0;
}