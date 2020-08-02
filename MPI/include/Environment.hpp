#ifndef SCIENTIFICCOMPUTING_MPI_ENVIRONMENT_HPP
#define SCIENTIFICCOMPUTING_MPI_ENVIRONMENT_HPP

namespace MPI {
class Environment {
public:
    Environment(const Environment& other) = delete;
    Environment& operator=(const Environment& other) = delete;

    Environment(Environment&& other) = delete;
    Environment& operator=(Environment&& other) = delete;

    Environment();
    Environment(int& argc, char**& argv);

    ~Environment();
    [[nodiscard]] int GetSize() const;

private:
    int size_{};

    void Init();
    void Init(int& argc, char**& argv);
};
} // namespace MPI

#endif // SCIENTIFICCOMPUTING_MPI_ENVIRONMENT_HPP
