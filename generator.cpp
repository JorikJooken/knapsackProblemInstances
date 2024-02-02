#include <iostream>
#include <random>
#include <cstdint>

using Integer = std::int64_t;

int main()
{
    std::cerr << "n=" << std::endl;
    Integer n;
    std::cin >> n;
    std::cerr << "capacity=" << std::endl;
    long long cap;
    std::cin >> cap;
    std::cerr << "classes=" << std::endl; // >= 2
    Integer classes;
    std::cin >> classes;
    classes--;
    std::cerr << "fraction=" << std::endl; // 0<=frac<=1, in practice frac should be quite a lot smaller than 1
    double frac;
    std::cin >> frac;
    std::cerr << "eps=" << std::endl;
    double eps;
    std::cin >> eps;
    std::cerr << "small=" << std::endl;
    long long small;
    std::cin >> small;

    std::mt19937 generator(1234);
    std::uniform_int_distribution<Integer> distribution(1,small);
    std::cout << n << std::endl;
    Integer amountSmall=n*frac;
    Integer am1=(n-amountSmall)/classes;
    double denominator=2.0;
    Integer amountCtr=0;
    for(Integer j=0; j<classes; j++)
    {
        for(Integer i=0; i<am1; i++)
        {
            Integer num1=distribution(generator);
            Integer num2=distribution(generator);
            std::cout << amountCtr << " " << (Integer)((1/denominator+eps)*cap+num1) << " " << (Integer)((1/denominator+eps)*cap+num2) << std::endl;
            amountCtr++;
        }
        denominator*=2;
    }
    for(Integer i=amountCtr; i<n; i++)
    {
        Integer num1=distribution(generator);
        Integer num2=distribution(generator);
        std::cout << i << " " << num1 << " " << num2 << std::endl;
    }
    std::cout << cap << std::endl;
    return 0;
}
