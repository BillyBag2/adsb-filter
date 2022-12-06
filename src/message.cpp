
#include <iostream>

#include "message.hpp"
#include "primitives.hpp"

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
        std::string lat_string = line.substr(line.find(',',15),line.find(',',16));
        std::string long_string = line.substr(line.find(',',16),line.find(',',17));
        try
        {
            double latitude = std::stod(lat_string);
            double longitude = std::stod(long_string);
            point = Point(longitude, latitude);
        }
        catch(std::exception e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return point;
}