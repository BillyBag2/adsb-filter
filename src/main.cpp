
#include <iostream>
#include <string>
#include <map>

#include "message.hpp"

int main(int argc, char ** argv)
{
    std::map<std::string, Point> all;
    std::map<std::string, bool> inside;
    Region uk(-8.27, 1.83, 49.8, 58.7);

    while(true)
    {
        std::string line;
        std::getline(std::cin, line);
        //std::cerr << "Got line \"" << line << "\"" << std::endl; 
        Message message = Message(line);
        Point coords = message.Coordinates();
        std::string sid = message.Sid();

        if(coords.Valid())
        {
            // std::cerr << "Coords: " << coords.Longitute() << "," << coords.Latitude() << std::endl;
            all[sid] = coords;
            inside[sid] = uk.Contains(coords);
        }

        if (inside[sid])
        {
            std::cout << message.Line() << std::endl;
        }

    }
    return 0;
}