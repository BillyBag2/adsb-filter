
#include <iostream>
#include <string>
#include <set>

#include "message.hpp"

/// @brief A boarder as we can see planes out to sea.
constexpr double boarder = 1.0;

int main(int argc, char ** argv)
{
    // Is inside the region.
    std::set<std::string> inside;

    // Approximate U.K region
    Region uk(
        -8.27 - boarder,
        1.83 + boarder,
        49.8 - boarder,
        58.7 + boarder);

    while(true)
    {
        std::string line;
        std::getline(std::cin, line);
        Message message = Message(line);
        Point coords = message.Coordinates();
        std::string sid = message.Sid();

        if(coords.Valid())
        {
            if(uk.Contains(coords))
            {
                inside.insert(message.Sid());
                std::cout << message.Line() << std::endl;
            }
            else
            {
                inside.erase(message.Sid());
            }
        }
        else if (inside.find(message.Sid()) != inside.end())
        {
            std::cout << message.Line() << std::endl;
        }
    }
    return 0;
}