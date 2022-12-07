
#include <iostream>

#include "message.hpp"
#include "primitives.hpp"

std::string Item(std::string line, int index)
{
    //std::cerr << "Line: " << line << std::endl << std::endl ;
    int count = 0;
    int off1 = 0;
    int off2 = 0;
    //std::cerr << line.size() << std::endl << std::endl ;
    for(unsigned int i = 0; i < line.size(); i++)
    {
        //std::cerr << line[i] << std::endl;
        if(line[i] == ',')
        {
            count ++;
            if(count == (index - 1))
            {
                off1 = i;
                //std::cerr << "off1:" << off1 << std::endl;
                continue;
            }
            if (count == index)
            {
                off2 = i;
                //std::cerr << "off2:" << off2 << std::endl;
                break;
            }
        }
    }
    std::string item = line.substr(off1 + 1, (off2 - off1) - 1);
    //std::cerr << "Item:" << item << std::endl;
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

        // std::cerr << "Coords: " << long_string << "," << lat_string << std::endl;

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

std::string Message::Sid()
{
    return Item(Line(), 3);
}

std::string Message::Line()
{
    return line;
}