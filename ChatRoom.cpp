#include "ChatRoom.hpp"

ChatRoom::ChatRoom(string IPAddress, uint16_t port)
{
    this->IPAddress = IPAddress;
    this->port = port;
    this->server = Server(IPAddress, port);
    this->connections.reserve(10);
    this->continueListening = true;
}

ChatRoom::~ChatRoom()
{
    Shutdown();
}

void ChatRoom::Startup()
{ 
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
    }
    this->continueListening = false;
    server.Disconnect();
}

void ChatRoom::ListenForConnections()
{
    // Thread handler for accepting connections 
    // Accept connections when admit thread is not active.
    if(this->server.Accept() > 0)
    {
        if(this->connections.size() <= MAX_CONNECTIONS) //Add client 
        {
            Admit();   
        }
        else
        {
            //reject connection.
            server.Send("Chatroom is full.");
        }
        
        this_thread::sleep_for(chrono::milliseconds(10));
        server.CloseConnection();

        if(continueListening)
        {
            //Continue Listening 
            ListenForConnections();
        }
    }
    
    
}

void ChatRoom::RemoveFromChatroom(int connectionID)
{
    //Locate user
    vector<User>::iterator userIterator = LocateUser(connectionID);

    cout<<"Thread terminated"<<endl;

    //Close socket
    (*userIterator).connection->CloseConnection();
    (*userIterator).connection->Disconnect();

    //free memory 
    free((*userIterator).connection);
    free((*userIterator).messageListener);

    //delete user from vector 
    this->connections.erase(userIterator);
    cout<<"Connections: "<<this->connections.size()<<endl;
}

void ChatRoom::ReadHandler(int connectionID)
{
    bool continueRead = true;
    vector<User>::iterator userIterator = LocateUser(connectionID);

    //Place thread to sleep allow new vector member to be added 
    this_thread::sleep_for(chrono::milliseconds(10));
    userIterator = LocateUser(connectionID);
    User user = (*userIterator);
    
    while(continueRead)
    {
        string newMessage;
        
        newMessage.clear();

        try
        {
            newMessage = (*(*userIterator).connection).Read();
        }
        catch(const NetworkError& e)
        {
            continueRead = false;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        if(newMessage != "")
        {
            cout<<newMessage<<endl;
        }
        
        newMessage = (*userIterator).username + ": " + newMessage;

        //broadcast 
        if(this->connections.size() > 0 && newMessage != "")
        {
            for(vector<User>::iterator it = this->connections.begin(); it < this->connections.end(); it++)
            {
                if(it != userIterator)
                {
                    //Critical section
                    (*it).connection->Send(newMessage);
                }
            }
        }
    }

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

void ChatRoom::Admit()
{
    int numOfTries = 0;
    Server *newConnection = new Server(this->IPAddress, this->port);
    int newClientID = -1;

    int newPort = newConnection->CreateListeningSocket();

    this->server.Send(to_string(newPort));
    this_thread::sleep_for(chrono::microseconds(10));

    newClientID = newConnection->Accept();
    string temp = newConnection->Read();
    
    numOfTries++;

    while(!DoesUserExist(temp) && numOfTries < 3)
    {
        newConnection->Send("false");

        temp.clear();
        temp = newConnection->Read();
        numOfTries++;
    }

    if(numOfTries < 3)
    {
        newConnection->Send("true");

        this->connections.push_back(User(newClientID, newPort, temp, newConnection, new thread(&ChatRoom::ReadHandler, this, newClientID))); 
        cout<<"connections: "<<this->connections.size()<<endl;
                
    }
    else
    {
        //wait for client to disconnect because of failure
        this_thread::sleep_for(chrono::milliseconds(50));

        //shutdown socket
        newConnection->CloseConnection();
        newConnection->Disconnect();
    }
}

bool ChatRoom::DoesUserExist(string name)
{
    bool result = true;

    for(vector<User>::iterator index = this->connections.begin(); index < this->connections.end(); index++)
    {
        if((*index).username == name)
        {
            result = false; 
        }
    }

    return result;
}