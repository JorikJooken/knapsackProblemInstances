#include <iostream>
#include <random>

int main()
{
    #define int long long

    std::cerr << "n=" << std::endl;
    int n;
    std::cin >> n;
    std::cerr << "capacity=" << std::endl;
    long long cap;
    std::cin >> cap;
    std::cerr << "classes=" << std::endl; // >= 2
    int classes;
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
    std::uniform_int_distribution<int> distribution(1,small);
    std::cout << n << std::endl;
    int amountSmall=n*frac;
    int am1=(n-amountSmall)/classes;
    double denominator=2.0;
    int amountCtr=0;
    for(int j=0; j<classes; j++)
    {
        for(int i=0; i<am1; i++)
        {
            int num1=distribution(generator);
            int num2=distribution(generator);
            std::cout << amountCtr << " " << (int)((1/denominator+eps)*cap+num1) << " " << (int)((1/denominator+eps)*cap+num2) << std::endl;
            amountCtr++;
        }
        denominator*=2;
    }
    for(int i=amountCtr; i<n; i++)
    {
        int num1=distribution(generator);
        int num2=distribution(generator);
        std::cout << i << " " << num1 << " " << num2 << std::endl;
    }
    std::cout << cap << std::endl;
    return 0;
}
