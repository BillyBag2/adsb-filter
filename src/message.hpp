#include <string>
#include "primitives.hpp"

/*
 *
 * Reference:
 * http://woodair.net/sbs/article/barebones42_socket_data.htm
 * 
 */

/**
 * Message types. 
 */
enum class MessageId
{
    MSG_1 = 1,
    MSG_2 = 2,
    MSG_3 = 3,
    MSG_4 = 4,
    Unknown = -1
};

class Message
{
public:
    Message(std::string line): line(line) {}
    MessageId Id();
    bool HasCoordinates();
    Point Coordinates();
private:
    std::string line;
    MessageId id {MessageId::Unknown};
    Point point {bad_point};
};