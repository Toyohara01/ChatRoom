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
enum Body {BodyNull, Pass, Fail, Message, Continue, Connect, Disconnect};
enum Type {TypeNull, Send, Receive};

//Structures
typedef struct MessageProperties
	{
		Header header;
		string userID;
		Body body;
		string message;
		Type type;

		MessageProperties()
		{
			this->header = Header::HeaderNull;
			this->userID.empty();
			this->body = Body::BodyNull;
			this->message.empty();
			this->type = Type::TypeNull;
		}

		MessageProperties(vector<string> input, Type messageType)
		{
			if(input.size() == 4) //attached message
			{
				if(input[0] == "INSTRUCTION")
					this->header = Header::Instruction;
				else if(input[0] == "STATUS")
					this->header = Header::Status;

				this->userID = input[1];

				if(input[2] == "PASS") 
					this->body = Body::Pass;
				else if(input[2] == "FAIL")
					this->body = Body::Fail;
				else if(input[2] == "MESSAGE")
					this->body = Body::Message;
				else if(input[2] == "CONTINUE")
					this->body = Body::Continue;
				else if(input[2] == "CONNECT")
					this->body = Body::Connect;
				else if(input[2] == "DISCONNECT")
					this->body = Body::Disconnect;

				this->message = input[3];
			}
			else //no message
			{
				if(input[0] == "INSTRUCTION")
					this->header = Header::Instruction;
				else if(input[0] == "STATUS")
					this->header = Header::Status;

				this->userID = input[1];

				if(input[2] == "PASS") 
					this->body = Body::Pass;
				else if(input[2] == "FAIL")
					this->body = Body::Fail;
				else if(input[2] == "MESSAGE")
					this->body = Body::Message;
				else if(input[2] == "CONTINUE")
					this->body = Body::Continue;
				else if(input[2] == "CONNECT")
					this->body = Body::Connect;
				else if(input[2] == "DISCONNECT")
					this->body = Body::Disconnect;
			}

			this->type = messageType;
		}
	}MessageProperties;

class Message
{
private: 
	string packet;
	MessageProperties messageProperties;
	time_t timestamp;
	string userID;
	Type messageType;

	time_t GetTime();

public:	
	Message(); 
    Message(string packet, Type messageType);
	vector<string> parse(string input);
    ~Message();
};

#endif //MESSAGE_HPP
