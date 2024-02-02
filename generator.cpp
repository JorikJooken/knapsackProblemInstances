#include <iostream>
#include <random>
#include <cstdint>
#include <stdexcept>

using Integer = std::int64_t;
using Real = double;

constexpr Integer RANDOM_SEED = 1234;

struct Parameter
{
    Integer n;
    Integer cap;
    Integer classes;
    Real frac;
    Real eps;
    Integer small;

    void read()
    {
        std::cerr << "n = " << std::endl;
        std::cin >> this->n;
        std::cerr << "capacity = " << std::endl;
        std::cin >> this->cap;
        std::cerr << "classes = " << std::endl; // >= 2
        std::cin >> this->classes;
        this->classes--;
        std::cerr << "fraction = " << std::endl; // 0<=frac<=1, in practice frac should be quite a lot smaller than 1
        std::cin >> this->frac;
        std::cerr << "eps = " << std::endl;
        std::cin >> this->eps;
        std::cerr << "small = " << std::endl;
        std::cin >> this->small;
    }

    void check()
    {
        if (this->n < 1)
        {
            throw std::invalid_argument("number of items parameter 'n' must be at least 1");
        }
        if (this->cap < 0)
        {
            throw std::invalid_argument("capacity paramenter 'c' of the knapsack must be a non-negative integer");
        }
        if (this->classes < 1) // 1 because the value is decremented just after being read
        {
            throw std::invalid_argument("classes parameter 'g' must an integer greater or equals 2");
        }
        if (this->frac < 0 || this->frac > 1)
        {
            throw std::invalid_argument("fraction parameter 'f' must be a real number between 0 and 1 (inclusive)");
        }
        if (this->eps < 0 || this->frac > 1)
        {
            throw std::invalid_argument("'epsilon' parameter must be a real number between 0 and 1 (inclusive)");
        }
        if (this->small < 0)
        {
            throw std::invalid_argument("paramenter 's' of the knapsack must be a non-negative integer");
        }
    }
};

int main()
{
    Parameter parameter;
    parameter.read();
    parameter.check();

    std::mt19937 generator(RANDOM_SEED);
    std::uniform_int_distribution<Integer> distribution(1, parameter.small);
    std::cout << parameter.n << std::endl;
    Integer amountSmall = parameter.n * parameter.frac;
    Integer am1 = (parameter.n - amountSmall) / parameter.classes;
    double denominator = 2.0;
    Integer amountCtr = 0;
    for (Integer j = 0; j < parameter.classes; j++)
    {
        for (Integer i = 0; i < am1; i++)
        {
            Integer num1 = distribution(generator);
            Integer num2 = distribution(generator);
            std::cout << amountCtr << " " << (Integer)((1 / denominator + parameter.eps) * parameter.cap + num1) << " " << (Integer)((1 / denominator + parameter.eps) * parameter.cap + num2) << std::endl;
            amountCtr++;
        }
        denominator *= 2;
    }
    for (Integer i = amountCtr; i < parameter.n; i++)
    {
        Integer num1 = distribution(generator);
        Integer num2 = distribution(generator);
        std::cout << i << " " << num1 << " " << num2 << std::endl;
    }
    std::cout << parameter.cap << std::endl;
    return 0;
}
