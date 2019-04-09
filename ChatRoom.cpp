#include "ChatRoom.hpp"

ChatRoom::ChatRoom(string IPAddress, uint16_t port)
{
    this->server = Server(IPAddress, port);

    // Create list of available ports
    for(int i = 1; i <= MAX_CONNECTIONS; i++)
    {
        this->availablePorts.push_back(port + i);
    }
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
    this->server.CreateListeningSocket();
}

void ChatRoom::Shutdown()
{
    //Close all connections. 
}

void ChatRoom::ListenForConnections()
{
    // Thread handler for accepting connections 
    // Accept connections 
    int newConnection = this->server.AcceptListeningSocket();
    
    if(this->connections.size() <= MAX_CONNECTIONS) //Add client 
    {   
        uint16_t port = this->availablePorts.front();
        this->availablePorts.erase(this->availablePorts.begin());

        this_thread::sleep_for(chrono::milliseconds(10)); //wait for message to send.

        //Send client new port to connect to.
        server.Send(newConnection, to_string(port));

        cout<<"Creating Thread"<<endl;
        thread admitNewUser(&ChatRoom::Admit, this, port);
    }
    else
    {
        Reject(newConnection); 
    }
    
    cout<<"Disconnectign"<<endl;
    server.Disconnect(newConnection);

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


void ChatRoom::Admit(uint16_t port)
{
    cout<<"Creating socket"<<endl;
    while(true);
    int newConnectionListener = server.CreateSocket(port);
    int newCientID = server.AcceptClientConnection(newConnectionListener);

    cout<<server.Read(newCientID)<<endl;
}