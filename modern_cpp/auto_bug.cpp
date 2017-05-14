#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, int> map {{"Hello", 1}, {"World", 2}};
    for(std::pair<std::string, int>& pair: map)
    {
        pair.second *= 10;
    }
    for(const auto& pair: map)
    {
        std::cout << pair.second << std::endl;
    }
    return 0;
}