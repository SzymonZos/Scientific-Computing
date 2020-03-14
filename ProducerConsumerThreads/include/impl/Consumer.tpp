#ifndef PRODUCERCONSUMERTHREADS_CONSUMER_TPP
#define PRODUCERCONSUMERTHREADS_CONSUMER_TPP

namespace DataFlow {
    template<class T>
    Consumer<T>::Consumer(std::shared_ptr<Queue<T>> pQueue) :
            pQueue_{pQueue},
            thread_{&Consumer<T>::TakeFromQueue, this} {}

    template<class T>
    Consumer<T>::~Consumer() {
        if(thread_.joinable()) {
            thread_.join();
        }
    }

    template<class T>
    T Consumer<T>::SortElement() {
        return nullptr;
    }

    template<class T>
    void Consumer<T>::TakeFromQueue() {

    }
}

#endif //PRODUCERCONSUMERTHREADS_CONSUMER_TPP