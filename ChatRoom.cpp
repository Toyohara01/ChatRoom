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
    if(this->connections.size() > 0)
    {
        for(vector<User>::iterator index = this->connections.begin(); index < this->connections.end(); index++)
        {
            RemoveFromChatroom((*index).connectionID);
        }

        server.Disconnect();
    }
}

void ChatRoom::ListenForConnections()
{
    // Thread handler for accepting connections 
    // Accept connections when admit thread is not active.
    if(this->admitNewUser.joinable())
    {
        this->admitNewUser.join();
    }
    int newConnection = this->server.AcceptListeningSocket();
    
    if(this->connections.size() <= MAX_CONNECTIONS) //Add client 
    {   
        uint16_t port = this->availablePorts.front();
        this->availablePorts.erase(this->availablePorts.begin());

        this_thread::sleep_for(chrono::milliseconds(10)); //wait for message to send.

        //Send client new port to connect to.
        server.Send(newConnection, to_string(port));

        this->admitNewUser = thread(&ChatRoom::Admit, this, port);
    }
    else
    {
        Reject(newConnection); 
    }
    
    server.Disconnect(newConnection);

    //Continue Listening 
    ListenForConnections();
}

void ChatRoom::RemoveFromChatroom(int connectionID)
{
    //Locate user
    vector<User>::iterator userIterator = LocateUser(connectionID);

    //Close socket
    server.Disconnect(connectionID);
    server.Disconnect((*userIterator).listeningSocketID);

    this->availablePorts.push_back((*userIterator).port);

    //Terminate listening thread for user 
    (*userIterator).continueReading = false;

    //Wait for thread to terminate
    if((*userIterator).messageListener->joinable())
    {
        (*userIterator).messageListener->join();
    }

    //delete user from vector 
    this->connections.erase(userIterator);
}

void ChatRoom::ReadHandler(int connectionID)
{
    bool continueRead = true;
    vector<User>::iterator userIterator = LocateUser(connectionID);

    cout<<"ReadHandler() reached."<<endl;
    while(continueRead)
    {
        cout<<server.Read(connectionID)<<endl;

        continueRead = (*userIterator).continueReading;
    }
}

void ChatRoom::Reject(int connectionID)
{
    server.Send(connectionID, "Chatroom is full.");

    RemoveFromChatroom(connectionID);
}

vector<User>::iterator ChatRoom::LocateUser(int connectionID)
{
    vector<User>::iterator it;

    for(vector<User>::iterator index = this->connections.begin(); index < this->connections.end(); index++)
    {
        if((*index).connectionID == connectionID)
        {
            it = index;
        }
    }

    return it;
}

void ChatRoom::Admit(uint16_t port)
{
    int numOfTries = 0;
    int newConnectionListener = server.CreateSocket(port);
    int newClientID = server.AcceptClientConnection(newConnectionListener);
    string temp = server.Read(newClientID);
    
    numOfTries++;

    while(!DoesUserExist(temp) && numOfTries < 3)
    {
        server.Send(newClientID, "false");

        temp.clear();
        temp = server.Read(newClientID);
        numOfTries++
    }

    if(numOfTries < 3)
    {
        User newUser = User(newConnectionListener, newClientID, port, temp, new thread(&ChatRoom::ReadHandler, this, newClientID));

        this->connections.push_back(newUser);
    }
    else
    {
        //wait for client to disconnect because of failure
        this_thread::sleep_for(chrono::milliseconds(50));

        server.Disconnect(newClientID);
    }
}

bool ChatRoom::DoesUserExist(string name)
{
    bool result = false;

    for(vector<User>::iterator index = this->connections.begin(); index < this->connections.end(); index++)
    {
        if((*index).username == name)
        {
            result = true; 
        }
    }

    return result;
}