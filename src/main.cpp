
#include <iostream>
#include <string>

#include "message.hpp"

int main(int argc, char ** argv)
{
    while(true)
    {
        std::string line;
        std::getline(std::cin, line);
        Message message = Message(line);
        if(message.HasCoordinates())
        {
            
        }
    }
    return 0;
}