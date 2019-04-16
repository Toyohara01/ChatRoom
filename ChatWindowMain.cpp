#include "ChatWindow.hpp"

int main(int argc, char** argv)
{
    enum menuChoices {LOGIN = 1};
    vector<class Message> messages;
    messages.clear();

    // Get IP Address and port of server to connect to. 
    string IPAddress = "127.0.0.1";
    uint16_t Port = 55500; //Hardcode for initial connection then reassign once connection is made 
   
    class ChatWindow window(IPAddress, Port);

    //Add logic for menu. 
    while(true)
    {
        cout<<"Menu:"<<endl<<"1) Login to chatroom"<<endl; //add more functionality 
        string userChoiceStr;
        
        getline(cin, userChoiceStr);
        
        int userChoice = stoi(userChoiceStr);

        switch (userChoice)
        {
        case LOGIN:
            window.Login();
            break;
        
        default:
            cout<<"Invalid choice entered please try again."<<endl;
            break;
        }

        //clear input buffer for next user input 
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}