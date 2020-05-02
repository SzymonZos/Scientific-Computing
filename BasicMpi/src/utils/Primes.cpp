#include "utils/Primes.hpp"

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