#include <bits/stdc++.h>

using namespace std;

double eps;

int main()
{
    #define int long long

    cerr << "n=" << endl;
    int n;
    cin >> n;
    cerr << "capacity=" << endl;
    long long cap;
    cin >> cap;
    cerr << "classes=" << endl; // >= 2
    int classes;
    cin >> classes;
    classes--;  
    cerr << "fraction=" << endl; // 0<=frac<=1, in practice frac should be quite a lot smaller than 1
    double frac;
    cin >> frac;
    cerr << "eps=" << endl;
    double eps;
    cin >> eps;
    cerr << "small=" << endl;
    long long small;
    cin >> small;

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(1,small);
    cout << n << endl;
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
            cout << amountCtr << " " << (int)((1/denominator+eps)*cap+num1) << " " << (int)((1/denominator+eps)*cap+num2) << endl;
            amountCtr++;
        }
        denominator*=2;
    }
    for(int i=amountCtr; i<n; i++)
    {
        int num1=distribution(generator);
        int num2=distribution(generator);
        cout << i << " " << num1 << " " << num2 << endl;
    }
    cout << cap << endl;
    return 0;
}
