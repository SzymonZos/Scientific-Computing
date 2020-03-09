#include "dataflow/Producer.hpp"
#include <random>

template<class T>
DataFlow::Producer<T>::Producer(uint32_t noElements) :
    noElements_{noElements},
    element_{} {}

template<class T>
void DataFlow::Producer<T>::GenerateRandomNumbers() {
    std::random_device randomDevice;
    std::mt19937 randomNumberGenerator(randomDevice());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    auto randomInt = dist6(randomNumberGenerator);
}

template<class T>
void DataFlow::Producer<T>::InsertIntoQueue(std::queue<T>& element) {

}
