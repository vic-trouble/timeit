#include <iostream>
#include <random>

#include <timeit/timeit.h>

int main()
{
    std::minstd_rand rnd;
    std::cout << timeit::total<std::chrono::nanoseconds>([&rnd](){ rnd(); }, 10000000).count() << " ns" << std::endl;

    return 0;
}