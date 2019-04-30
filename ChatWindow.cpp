#include "ChatWindow.hpp"
#include "Archive.hpp"
#include "Crypto.hpp"

ChatWindow::ChatWindow(string ip, uint16_t port)
{
    this->ip = ip;
    this->port = port;
}

void ChatWindow::Connect()
{
    this->sockID = client.Connect(this->ip, this->port);
}
/* 
 *  Reads user input to for access to features.
 * 
 * 
 * 
 */
void ChatWindow::StringInterpreter(string input) //Create new message structure populate data send then display. 
{
    Enigma encryptObj;
    Archive storageObj;

    if(input == "quit")
    {
        this->continueSession = false;
        this->client.Disconnect();
    }
    else
    {
        //encrypt input before sending. LAD
        input = encryptObj.callEncrypt(input);

		storageObj.Save(input);
		
		client.Send(input); 
    }
    //Ideally it'll check to see if a defined function was entered execute that process 
    //but for now it'll display and send that input to other clients
}

/*
 * Processes message. 
 * 
 */
void ChatWindow::ProcessMessage(string input) //change to message input later 
{
    cout<<input<<endl;

    this_thread::sleep_for(chrono::milliseconds(10));
}

bool ChatWindow::Login()
{
    string username;
    string portString;
    string usernameStatusResponse;
    bool admitStatus = false;
    int numOfTries = 0;
    
    cout<<"Please enter a username: "; 
    username.clear();
    getline(cin, username);
    numOfTries++;

    cout<<"Connecting to Server...";

    Connect();

    //Get port 
    portString = client.Read();
   
    //Disconnect
    Disconnect();

    if(portString != "")
    {
        //Get new port
        this->port = (uint16_t)stoul(portString, nullptr);
    }

    //Wait a bit for server to setup new socket
    this_thread::sleep_for(chrono::milliseconds(50));

    //Connect to new socket
    Connect();

    //Send username
    client.Send(username);

    //Loop while server approves username
    while((usernameStatusResponse = client.Read()) != "true" && numOfTries < 3)
    {    
        usernameStatusResponse.clear();

        //Clear string
        username.clear();

        cout<<endl<<endl<<"Username exists in chatroom already. Enter a different username."<<endl
            <<"Please enter a username: "; 

        username.clear();
        getline(cin, username);

        client.Send(username); 

        numOfTries++;
    }

    if(usernameStatusResponse == "true")
    {
        admitStatus = true;
    }

    return admitStatus;
}

void ChatWindow::Chat()
{
    cout<<"Entering Chat Session..."<<endl;
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

    this->readMessagesThread.join();
}

void ChatWindow::readMessageHandler()
{
    Enigma decryptObj;
    Archive storageObj;

    //thread garbageCollector(&ChatWindow::GarbageCollector, this);

    while(continueSession)
    {
        string stringReceived;

        try
        {
            stringReceived = client.Read();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(const NetworkError& e)
        {
            this->continueSession = false;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        //save encrypted string that was received
        storageObj.save(input);

        //Decrypt string for reading
        stringReceived = decryptObj.callDecrypt(stringReceived);

        ProcessMessage(stringReceived);
        //this->processMessagesThreadBuffer.push_back(thread(&ChatWindow::ProcessMessage, this, stringReceived));
    }

    //garbageCollector.join();

    this_thread::sleep_for(chrono::milliseconds(10));
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

        this_thread::sleep_for(chrono::seconds(10));
    }
}

void ChatWindow::Logout()
{
    //Send logout command to server. 

    Disconnect();

    this->port = 55500; // reset port for reconnection
}

void ChatWindow::Disconnect()
{
    client.Disconnect();
}
