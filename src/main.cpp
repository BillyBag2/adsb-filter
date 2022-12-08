
#include <iostream>
#include <string>
#include <set>
#include <ctime>
#include <memory>

#include "message.hpp"

/// @brief A boarder as we can see planes out to sea.
constexpr double boarder = 1.0;

/// @brief  Only check time after this many messages.
constexpr int kMesssagesPerTimecheck = 10000;

static int HourOfDay()
{
    // Written by ChatGPT. Did not check it.
    std::time_t t = std::time(nullptr);
    std::tm* localtime = std::localtime(&t);
    return localtime->tm_hour;
}


int main(int argc, char ** argv)
{
    int the_hour = 0;
    int new_hour = 0;
    int time_check_counter = kMesssagesPerTimecheck;

    // Is inside the region.
    auto inside = std::make_shared<std::set<std::string>>();
    auto cache  = std::make_shared<std::set<std::string>>();

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
        std::string hex_ident = message.HexIdent();

        if(coords.Valid())
        {
            cache->erase(hex_ident);
            if(uk.Contains(coords))
            {
                
                inside->insert(hex_ident);
                std::cout << message.Line() << std::endl;
            }
            else
            {
                inside->erase(hex_ident);
            }
        }
        else if (inside->find(hex_ident) != inside->end())
        {
            std::cout << message.Line() << std::endl;
        }

        // Count messages and check if hour has rolled over every now and then.
        time_check_counter--;
        if(0 == time_check_counter)
        {
            // Lets check the hour.
            time_check_counter = kMesssagesPerTimecheck;
            new_hour = HourOfDay();
            if(new_hour != the_hour)
            {
                the_hour = new_hour;
                // Hour has rolled over.
                auto temp = inside;
                inside = cache;
                cache = temp;
                inside->clear();
            }
        }
    }
    return 0;
}