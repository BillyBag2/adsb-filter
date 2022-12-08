
#include <iostream>

#include "message.hpp"
#include "primitives.hpp"

std::string Item(std::string line, int index)
{
    int count = 0;
    int off1 = 0;
    int off2 = 0;

    for(unsigned int i = 0; i < line.size(); i++)
    {
        if(line[i] == ',')
        {
            count ++;
            if(count == (index - 1))
            {
                off1 = i;
                continue;
            }
            if (count == index)
            {
                off2 = i;
                break;
            }
        }
    }
    std::string item = line.substr(off1 + 1, (off2 - off1) - 1);
    return item;
}

MessageId Message::Id()
{
    if(id != MessageId::Unknown)
    {
        return id;
    }

    if(line.substr(0,4) != "MSG,")
    {
        return MessageId::Unknown;
    }

    std::string msg_id = line.substr(4);
    msg_id = msg_id.substr(0,msg_id.find(','));
    try
    {
        id = static_cast<MessageId>(std::stoi(msg_id));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return id;
}

bool Message::HasCoordinates()
{
    MessageId id = Id();
    switch(id)
    {
        case MessageId::MSG_3:
        case MessageId::MSG_2:
            return true;
        default:
            return false;
    }
}

Point Message::Coordinates()
{
    if(HasCoordinates())
    {
        std::string lat_string = Item(line, 15);
        std::string long_string = Item(line, 16);

        try
        {
            double latitude = std::stod(lat_string);
            double longitude = std::stod(long_string);
            point = Point(longitude, latitude);
        }
        catch(std::exception const &e)
        {
            std::cerr << e.what() << '\n';
            std::cerr << "Failed to get coords." << std::endl;
        }
    }
    return point;
}

std::string Message::HexIdent()
{
    std::string hex_ident = Item(Line(), 5);
    return hex_ident;
}

std::string Message::Line()
{
    return line;
}