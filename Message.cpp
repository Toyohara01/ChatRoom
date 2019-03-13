#include "Message.hpp"

Message::Message()
{
    
}

Message::Message(string packet, string userID, MessageType messageType)
{
    this->packet = packet;
    this->messageType = messageType;
    this->userID = userID;
    this->timestamp = GetTime();
    this->messageProperties = MessageProperties();
}

Message::~Message()
{

}

vector<string> Message::parse(string input)
{

}

void Message::process()
{
    
}

time_t Message::GetTime()
{
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
}