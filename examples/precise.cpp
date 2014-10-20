#include <iostream>
#include <string>
#include <random>

#include <timeit/timeit.h>

template <typename Random>
void benchmark(const std::string &engine, size_t iterations)
{
    Random rnd;
    std::cout << engine << " - " << timeit::average<std::chrono::nanoseconds>([&rnd](){ rnd(); }, iterations).count() << " ns" << std::endl;
}

int main()
{
    auto iterations = 1000000;
    benchmark<std::minstd_rand>("minstd_rand");
    benchmark<std::mt19937>("mt19937");
    benchmark<std::ranlux24>("ranlux24");
    benchmark<std::knuth_b>("knuth_b");
    return 0;
}