#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

int main()
{
    auto vec = std::make_unique<std::vector<int>>(10, 20);
    std::for_each(vec->cbegin(), vec->cend(), [](auto e) { std::cout << e << std::endl; });
    return 0;
}