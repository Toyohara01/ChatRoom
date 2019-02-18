#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Message
{
private: 
	string content;
	time_t timestamp;
	string userID;

public:
    Message();
	vector<string> parse(string input);
	void process();
    ~Message();
};

#endif //MESSAGE_HPP
