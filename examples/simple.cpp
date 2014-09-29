#include <chrono>
#include <iostream>
#include <thread>

#include <timeit/timeit.h>

void sleep100ms()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main()
{
    std::cout << "elapsed " << timeit::min(sleep100ms).count() << " ms" << std::endl;
    return 0;
}