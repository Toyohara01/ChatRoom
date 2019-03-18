#include "Message.hpp"

Message::Message()
{

}

Message::Message(string packet, Type messageType)
{
    this->packet = packet;
    this->messageType = messageType;
    this->timestamp = GetTime();
    this->messageProperties = MessageProperties(parse(this->packet), this->messageType);
}

Message::~Message()
{

}

vector<string> Message::parse(string input)
{
    string temp;
    vector<string> output;

    temp.clear();
    output.clear();

    for(int index = 0; index < input.length(); index++)
    {
        if(input[index] != MSG_DELIM)
            temp += input[index];
        else 
        {
            if(temp != MSG_FOOTER)
            {
                index++;
                output.push_back(temp);
                temp.clear();
            }
        }
    }

    return output;
}

time_t Message::GetTime()
{
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
}