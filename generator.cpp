#include <iostream>
#include <random>
#include <cstdint>
#include <stdexcept>
#include <vector>

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
    Real b = 2.0;

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

class Item
{
public:
    Item(const Integer identifier, const Integer profit, const Integer weight)
        : identifier(identifier), profit(profit), weight(weight) {}

    void print() const
    {
        std::cout << identifier << " " << profit << " " << weight << std::endl;
    }

private:
    Integer identifier;
    Integer profit;
    Integer weight;
};

struct Instance
{
    Parameter parameter;
    Integer number_of_small_items;
    Integer number_of_items_in_a_group;
    std::vector<Item> items;

    Instance(const Parameter parameter)
        : parameter(parameter)
    {
        Integer approximate_number_of_small_items = parameter.n * parameter.frac;
        this->number_of_items_in_a_group = (parameter.n - approximate_number_of_small_items) / parameter.classes;
        const Integer number_of_large_items = parameter.classes * this->number_of_items_in_a_group;
        this->number_of_small_items = parameter.n - number_of_large_items;
    }

    void add_large_item(const Real denominator, const Integer r1, const Integer r2, const Parameter &parameter)
    {
        const Integer identifier = this->items.size();
        const Integer profit = ((1 / denominator) + parameter.eps) * parameter.cap + r1;
        const Integer weight = ((1 / denominator) + parameter.eps) * parameter.cap + r2;
        items.push_back(Item(identifier, profit, weight));
    }

    void add_small_item(const Integer r1, const Integer r2)
    {
        items.push_back(Item(this->items.size(), r1, r2));
    }

    void print() const
    {
        std::cout << parameter.n << std::endl;
        for (const Item &item : this->items)
        {
            item.print();
        }
        std::cout << parameter.cap << std::endl;
    }
};

class Random
{
public:
    Random(const Parameter &parameter)
        : generator(RANDOM_SEED), distribution(1, parameter.small) {}

    Integer get()
    {
        return distribution(generator);
    }

private:
    std::mt19937 generator;
    std::uniform_int_distribution<Integer> distribution;
};

int main()
{
    Parameter parameter;
    parameter.read();
    parameter.check();

    Random random(parameter);

    Instance instance(parameter);

    // generate large items
    Real denominator = parameter.b;
    for (Integer group_counter = 0; group_counter < parameter.classes; group_counter++)
    {
        for (Integer item_counter = 0; item_counter < instance.number_of_items_in_a_group; item_counter++)
        {
            Integer r1j = random.get();
            Integer r2j = random.get();
            instance.add_large_item(denominator, r1j, r2j, parameter);
        }
        denominator *= parameter.b;
    }

    // generate small items
    for (Integer item_counter = 0; item_counter < instance.number_of_small_items; item_counter++)
    {
        Integer r1j = random.get();
        Integer r2j = random.get();
        instance.add_small_item(r1j, r2j);
    }

    // print instance to standard output
    instance.print();

    return 0;
}
