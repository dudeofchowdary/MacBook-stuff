#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cassert>

typedef long long NUMBER;
const NUMBER NA = -1;

struct Designs
{
    Designs(int s);
    void load();
    void run();    
    NUMBER stackDesigns(int i, int level);
    void setCompatible();
    void showCache() const;
private:
    const int stripes;
    std::vector<int> v;
    std::vector<std::vector<int>> compatible;  
    std::vector<std::vector<NUMBER>> cache;
};

void Designs::showCache() const
{
    std::size_t i = 0;
    for (auto& v: cache)
    {
        std::cerr << "cache[" << i << "] = ";
        for (auto d: v)
            std::cerr << d << ", ";
        std::cerr << "\n";
        ++i;
    }
}

Designs::Designs(int s) : stripes(s)
{
}

void Designs::setCompatible()
{
    for (std::size_t i = 0; i != v.size(); ++i)
    {
        std::vector<int> c;
        for (std::size_t n = 0; n != v.size(); ++n)
        {
            if ((v[i] & v[n]) == 0b100000000000000000000000000000)
            {
                c.push_back(n);
            }
        }
       compatible.push_back(c);
    }
}

void Designs::load()
{
	int n;
	while(std::cin >> n)
	{
	  	v.push_back(n);
		std::string s;
		std::cin >> s;
	}
	std::cerr << "Total possible combinations of length 30: " << v.size() << "\n";
    for (std::size_t i = 0; i != v.size(); ++i)
    {
        std::vector<NUMBER> v = std::vector<NUMBER>(stripes, NA);
        cache.push_back(v);
    }
}

NUMBER Designs::stackDesigns(int i, int heigth)
{
    if (heigth == 0)
    {
        return 1;
    }
    if (heigth == 1)
    {
        return compatible[i].size();
    }
    NUMBER& ret = cache[i][heigth - 1];

    if (ret != NA)
        return ret;
    ret = 0;
    for (auto n: compatible[i])
    {
        ret += stackDesigns(n, heigth - 1);
    }

    return ret;
}

void Designs::run()
{
    NUMBER ret = 0;
    for (size_t i = 0; i != v.size(); ++i)
    {
        ret += stackDesigns(i, stripes - 1);
    }
	std::cerr << "Total number of floor designs which have 11 strips of length 30: " << ret << "\n";
}

int main(int argc, char* argv[])
{
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    int stripes = 11;
    Designs d(stripes);
    d.load();
    d.setCompatible();
    d.run();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    
    std::cout << "Time taken for calculation of 11 stripes of length 30: " << elapsed_seconds.count()<<"\n";
    
	return 0;
}
