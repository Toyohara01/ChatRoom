#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using namespace std; //@@ Should we remove this and use std:: for everything? Coding style / reusability issue for later projects. 

// Constants
#define MSG_DELIM '_'
#define MSG_FOOTER "END"

//Enumerations 
enum Header {HeaderNull, Instruction, Status};
enum Body {BodyNull, Pass, Fail, Message, Connect, Disconnect};
enum Type {TypeNull, Send, Receive};
enum MessageType {MessageTypeNull, Sent, Received};

//Structures
typedef struct MessageProperties
	{
		Header header;
		Body body;
		Type type;

		MessageProperties()
		{
			header = Header::HeaderNull;
			body = Body::BodyNull;
			type = Type::TypeNull;
		}
	}MessageProperties;

class Message
{
private: 
	string packet;
	MessageProperties messageProperties;
	time_t timestamp;
	string userID;
	MessageType messageType;

	time_t GetTime();

public:	
	Message();
    Message(string packet, string userID, MessageType messageType);
	vector<string> parse(string input);
	void process();
    ~Message();
};

#endif //MESSAGE_HPP
