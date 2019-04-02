#include "Client.hpp"
#include "Message.hpp"

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void EndRead();
//void ProcessMessage(class Message input);
void ProcessMessage(string input);

int main(int argc, char** argv)
{
    vector<class Message> messages;
    messages.clear();

    // Get IP Address and port of server to connect to. 
    string IPAddress;
    uint16_t Port = 55890; //Hardcode for initial connection then reassign once connection is made 
    cout<<"Enter Server's IP Address format(xxx.xxx.xxx.xxx): "; getline(cin, IPAddress);
    cout<<"Running Server on Port:"<<Port<<endl; //cin>>Port; 
   
    class Client client(IPAddress, Port);

    //class Client client(IPAddress, Port);
    client.Connect();

    cout<<"Connected to Server"<<endl<<endl;
    client.BeginRead(ProcessMessage);

    while(true)
    {
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