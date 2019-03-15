#include "Client.hpp"
#include "Message.hpp"

#include <iostream>
#include <vector>

using namespace std;

void EndRead();
void ProcessMessage(class Message input);

int main(int argc, char** argv)
{
    vector<class Message> messages;
    messages.clear();
}

void ProcessMessage(class Message input)
{

}

void EndRead()
{
    string temp; // string returned frm Client.EndRead();
    //Call Client.EndRead(); Clear calling flag. 

    class Message newMessage(temp, Type::Receive);

    //launch new thread to process packet. 
}