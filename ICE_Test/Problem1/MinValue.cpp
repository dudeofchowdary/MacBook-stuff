
#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
int main()
{
    auto start =  chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    
    long long size = 128000000;
    set<float> elements;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 2000.0);
    auto size_5 = std::ceil((95 * size) / 100);
    size_5 = size - size_5;
    
    for (int n = 0; n < size; ++n) {
        if(elements.size() < size_5) {
            elements.insert(dis(gen));
        }
        else if(dis(gen) > *(std::next(elements.begin(),0))) {
            elements.erase(elements.begin());
            elements.insert(dis(gen));
        }
    }

    //cout<<"\nSet size: "<<elements.size()<<"\n\n";
    
    std::cout << "Smallest number that is larger than 95% of numbers: " << *(std::next(elements.begin(),0));
    
    auto end = chrono::high_resolution_clock::now();
    
    double time_taken =
          chrono::duration_cast<chrono::nanoseconds>(end - start).count();
      
    time_taken *= 1e-9;
      
    cout << "\nTime taken by program for input size 128,000,000 is : " << fixed
             << time_taken << setprecision(9);
    cout << " sec" << endl;
}
