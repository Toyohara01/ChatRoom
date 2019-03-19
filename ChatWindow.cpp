#include "Client.hpp"
#include "Message.hpp"

#include <iostream>
#include <vector>

using namespace std;

void EndRead();
//void ProcessMessage(class Message input);
void ProcessMessage(string input);

int main(int argc, char** argv)
{
    vector<class Message> messages;
    messages.clear();

    class Client client("192.168.0.26", 55689);
    client.Connect();

    while(true)
    {
        client.Read(ProcessMessage);
        string input;
        getline(cin, input);
        client.Send(input);
    }

}

/* void ProcessMessage(class Message input)
{

}*/

void ProcessMessage(string input)
{
    cout<<input<<endl;
}

void EndRead()
{
    string temp; // string returned frm Client.EndRead();
    //Call Client.EndRead(); Clear calling flag. 

    class Message newMessage(temp, Receive);

    //launch new thread to process packet. 
}