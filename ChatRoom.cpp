#include "Server.hpp"

#include <iostream>
#include <thread>

using namespace std;
 
class Server *server = NULL;

void ProcessMessage(string input);
void BeginRead()
{
    while(true)
    {
        server->Read(ProcessMessage);
    }
}

int main(int argc, char** argv)
{
    // Get IP Address and port of server to connect to. 
    string IPAddress;
    uint16_t Port = 55890;
    cout<<"Enter Server's IP Address format(xxx.xxx.xxx.xxx): "; getline(cin, IPAddress);
    cout<<"Running Server on Port:"<<Port<<endl; //cin>>Port; 

    server = new Server(IPAddress, 55890);

    //Server server(IPAddress, Port);
    server->CreateSocket();

    thread streamReader(BeginRead);

    while(true)
    {
        string input;
        getline(cin, input);
        server->Send(input);
    }
    //Archive archive("hello.txt");
}

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