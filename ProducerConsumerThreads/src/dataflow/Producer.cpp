#include "dataflow/Producer.hpp"

template<class T>
DataFlow::Producer<T>::Producer(uint32_t numElements) :
    numElements_(numElements) {}

template<class T>
void DataFlow::Producer<T>::GenerateRandomNumbers(uint32_t count) {

}

template<class T>
void DataFlow::Producer<T>::InsertIntoQueue(std::queue<T>& element) {
}
