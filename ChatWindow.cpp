#include "ChatWindow.hpp"

ChatWindow::ChatWindow(string ip, uint16_t port)
{
    this->ip = ip;
    this->port = port;
}

void ChatWindow::Connect()
{
    client = Client();
    this->sockID = client.Connect(this->ip, this->port);
}

/* 
 *  Reads user input to for access to features.
 * 
 * 
 * 
 */
void ChatWindow::StringInterpreter(string input)
{
    client.Send(this->sockID, input);
    cout<<"\t\t" + input<<endl;

    //Ideally it'll check to see if a defined function was entered execute that process 
    //but for now it'll display and send that input to other clients
}

/*
 * Processes message. 
 * 
 */
void ChatWindow::ProcessMessage(string input)
{
    cout<<input<<endl;
}

void ChatWindow::Login()
{
    string username;
    string portString;
    string usernameStatusResponse;
    bool admitStatus = false;
    int numOfTries = 0;
    

    cout<<"Please enter a username: "; 
    getline(cin, username);
    numOfTries++;

    cout<<"Connecting to Server...";
    Connect();

    //Get port 
    portString = client.Read(this->sockID);

    //Disconnect
    Disconnect(this->sockID);

    //Get new port
    this->port = (uint8_t)stoul(portString, nullptr, portString.length());

    //Wait a bit for server to setup new socket
    this_thread::sleep_for(chrono::milliseconds(50));

    //Connect to new socket
    Connect();

    //Send username
    client.Send(this->sockID, username);

    //Loop while server approves username
    while(client.Read(this->sockID) != "true" && numOfTries < 3)
    {
        if(usernameStatusResponse == "true")
        {
            admitStatus = true;
        }
        usernameStatusResponse.clear();

        //Clear string
        username.clear();

        //clear buffer
        cin.clear();

        cout<<endl<<endl<<"Username exists in chatroom already. Enter a different username."<<endl
            <<"Please enter a username: "; 
        getline(cin, username);
        client.Send(this->sockID,username);

        numOfTries++;
    }

    if(admitStatus)
    {
        Chat();
    }
}

void ChatWindow::Chat()
{
    this->continueSession = true;
    
    //Create thread for message listening 
    this->readMessagesThread = thread(&ChatWindow::readMessageHandler, this);

    while(continueSession)
    {
        string input;
        input.clear();

        getline(cin, input);

        StringInterpreter(input);
    }
}

void ChatWindow::readMessageHandler()
{
    while(continueSession)
    {
        string stringReceived = client.Read(this->sockID);

        this->processMessagesThreadBuffer.push_back(thread(&ChatWindow::ProcessMessage, this, stringReceived));
    }
}

void ChatWindow::GarbageCollector()
{
    while(this->continueSession)
    {
        vector<thread>::iterator threadPtr;

        if(this->processMessagesThreadBuffer.size() > 0)
        {
            for(threadPtr = this->processMessagesThreadBuffer.begin(); threadPtr < processMessagesThreadBuffer.end(); threadPtr++)
            {
                if((*threadPtr).joinable() == false)
                {
                    vector<thread>::iterator tempPtr = threadPtr;
                    threadPtr--;

                    this->processMessagesThreadBuffer.erase(tempPtr);
                }
            }
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
}

void ChatWindow::Logout()
{

}

void ChatWindow::Disconnect(int connectionID)
{
    client.Disconnect(this->sockID);
}
