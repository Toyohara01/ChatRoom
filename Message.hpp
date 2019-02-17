#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <ctime>

class Message
{
    private: 
	string content;
	time_t timestamp;
	string userID;

    public:
    Message();
	parse();
	process();
    ~Message();
};

#endif //MESSAGE_HPP
