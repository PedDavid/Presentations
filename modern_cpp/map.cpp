#include <iostream>
#include <string>
#include <map>

int main()
{
    std::map<int, std::string> map{{1, "Hello"}, {2, "World"}, {3, "!"}};
    int product = 1;
    for (const auto& val : map) {
        product *= val.first;
    }
    return 0;
}