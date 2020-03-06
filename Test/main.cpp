#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <thread>
#include <string>

class ThreadWrapper {
private:
    std::thread thread_;

public:
    ThreadWrapper() = default;
    ~ThreadWrapper() = default;

    ThreadWrapper(const ThreadWrapper& other) = delete;
    ThreadWrapper& operator=(const ThreadWrapper& other) = delete;

    ThreadWrapper(ThreadWrapper&& other) noexcept :
        thread_(std::move(other.thread_)){}

    ThreadWrapper& operator=(ThreadWrapper&& other) noexcept {
        if (thread_.joinable()) {
            thread_.join();
        }
        thread_ = std::move(other.thread_);
        return *this;
    }
    template<typename Fn, typename ...Args>
    explicit ThreadWrapper(Fn&& cb, Args&&... args) :
        thread_{cb, std::forward<Args>(args)...} {}

    template<typename Fn, typename ...Args>
    ThreadWrapper operator()(Fn&& cb, Args&&... args) {
        std::thread thread(cb, std::forward<Args>(args)...);
        thread.join();
    }
    std::thread& GetThread() {
        return thread_;
    }

};


namespace sroo {
    class foo {
    public:
        foo() = delete;
        ~foo() = default;

        foo(const foo& other) = default;
        foo& operator=(const foo& other) = default;

        foo(foo&& other) = default;
        foo& operator=(foo&& other) = default;

        explicit foo(bool test) : test{test}, vec{} {}
        bool test;
        std::vector<double> vec;
    };
}

template<typename T>
void print(T container) {
    for (const auto& value : container) {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;
}

void test(const std::string& str) {
    std::cout << str << std::endl;
}

int main() {
    sroo::foo A(false);
    std::vector<double> v = {1, -10, 6, 324.321};
    print(v);
    std::sort(v.begin(), v.end());
    print(v);
    A.test = true;

    uint32_t boo = 0;
    for (uint16_t i = 0; i < 3; i++) {
        std::cout << "in: " << std::hex << boo << std::endl;
        boo >>= 8;
        std::cout << "mid: " << std::hex << boo << std::endl;
        boo |= 0xFF000000;
        std::cout << "out: " << std::hex << boo << std::endl;

    }
    std::cout << std::hex << boo;

    A.vec = v;
    print(A.vec);

    sroo::foo B = std::move(A);
    print(A.vec);
    print(B.vec);

    ThreadWrapper th{test, "XD"};
    th(test, "LOL");
    th.GetThread().join();

    return 0;
}
