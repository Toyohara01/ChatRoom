#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using namespace std; //@@ Should we remove this and use std:: for everything? Coding style / reusability issue for later projects. 

// Constants
#define BUFFER_SIZE 1024
#define MSG_DELIM '_'
#define MSG_FOOTER "END"

//Enumerations 
enum Header {HeaderNull, Instruction, Status};
enum Body {BodyNull, Pass, Fail, Message, Connect, Disconnect};
enum Type {TypeNull, Send, Receive};

//Structures
typedef struct MessageProperties
	{
		Header header;
		Body body;
		Type type;
		string msg;

		MessageProperties()
		{
			header = Header::HeaderNull;
			body = Body::BodyNull;
			type = Type::TypeNull;
			msg.clear();
		}
	}MSG;

class Message
{
private: 
	string content;
	MessageProperties messageProperties;
	time_t timestamp;
	string userID;

public:	
    Message();
	vector<string> parse(string input);
	void process();
    ~Message();
};

#endif //MESSAGE_HPP
