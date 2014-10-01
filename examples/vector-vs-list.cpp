#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include <timeit/timeit.h>

template <typename Container>
void generate(Container &container, size_t n)
{
    int val = 0;
    std::generate_n(std::back_inserter(container), n, [&val](){ return val++; });
}

int main()
{
    constexpr size_t N = 1000000;

    std::vector<int> vector;
    std::list<int> list;

    auto sep = '\t';
    auto ms = "ms";
    std::cout << "op" << sep << "vector" << sep << "list" << std::endl;

    std::cout << "gen" 
        << sep << timeit::timeit([&](){ generate(vector, N); }).count() << ms
        << sep << timeit::timeit([&](){ generate(list, N); }).count() << ms << std::endl;

    std::cout << "find"
        << sep << timeit::timeit([&](){ std::find(begin(vector), end(vector), N / 2); }).count() << ms
        << sep << timeit::timeit([&](){ std::find(begin(list), end(list), N / 2); }).count() << ms << std::endl;

    std::cout << "clear"
        << sep << timeit::timeit([&](){ vector.clear(); }).count() << ms
        << sep << timeit::timeit([&](){ list.clear(); }).count() << ms << std::endl;

    return 0;
}