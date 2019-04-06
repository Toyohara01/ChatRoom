#include "ChatRoom.hpp"

ChatRoom::ChatRoom()
{
    string IPAddress = "192.168.0.71";

    uint16_t Port = 55890;

    this->server = Server(IPAddress, Port);
}

ChatRoom::~ChatRoom()
{
    Shutdown();
}

void ChatRoom::Startup()
{
    //Add method of finding what IP addresses are available. 
    // Get IP Address and port of server to connect to. 
    //cout<<"Enter Server's IP Address format(xxx.xxx.xxx.xxx): "; getline(cin, IPAddress);
    //cout<<"Running Server on Port:"<<Port<<endl; //cin>>Port; 

    this->server.CreateSocket();
}

void ChatRoom::Shutdown()
{
    //Close all connections. 
}

void ChatRoom::ListenForConnections()
{
    // Thread handler for accepting connections 
    // Accept connections 
    int newConnection = this->server.Accept();

    
    if(this->connections.size() <= MAX_CONNECTIONS) //Add client 
    {   
        User newUser(newConnection, "Connection " + to_string(this->connections.size()), new thread(&ChatRoom::ReadHandler, this, newConnection));        
        this->connections.push_back(newUser);
        cout<<"User admitted";
    }
    else
    {
        Reject(newConnection); 
    }
    

    //Continue Listening 
    ListenForConnections();
}

void ChatRoom::ReadHandler(int ConnectionID)
{
    cout<<"ReadHandler() reached."<<endl;
}

void ChatRoom::Reject(int connectionID)
{

}


void ChatRoom::Admit()
{

}