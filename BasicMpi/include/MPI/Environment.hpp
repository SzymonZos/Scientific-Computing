#ifndef SCIENTIFICCOMPUTING_ENVIRONMENT_HPP
#define SCIENTIFICCOMPUTING_ENVIRONMENT_HPP

namespace MPI {
class Environment {
public:
    Environment() = delete;
    Environment(const Environment& other) = delete;
    Environment& operator=(const Environment& other) = delete;

    Environment(Environment&& other) = delete;
    Environment& operator=(Environment&& other) = delete;

    Environment(int& argc, char**& argv);
    ~Environment();
    [[nodiscard]] int GetSize() const;

private:
    int size_{};

    void Init(int& argc, char**& argv);
};
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_ENVIRONMENT_HPP
