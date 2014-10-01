#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include <timeit/timeit.h>

template <template <typename, typename> class Container, size_t N>
void generate()
{
    Container<int, std::allocator<int>> v;
    int val = 0;
    std::generate_n(std::back_inserter(v), N, [&val](){ return val++; });
}

int main()
{
    constexpr size_t N = 1000000;
    auto sep = '\t';
    std::cout << "op" << sep << "vector" << sep << "list" << std::endl;
    std::cout << "gen" 
        << sep << timeit::min(generate<std::vector, N>, 10).count() << "ms"
        << sep << timeit::min(generate<std::list, N>, 10).count() << "ms" << std::endl;
    return 0;
}