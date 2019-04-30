#include "ChatWindow.hpp"

int main(int argc, char** argv)
{
    enum menuChoices {LOGIN = 1};
    vector<class Message> messages;
    messages.clear();
    string userChoiceStr;

    // Get IP Address and port of server to connect to. 
    string IPAddress = "127.0.0.1";
    uint16_t Port = 55500; //Hardcode for initial connection then reassign once connection is made 
   

    //Add logic for menu. 
    while(userChoiceStr != "quit")
    {
        cout<<"Menu:"<<endl<<"1) Login to chatroom"<<endl; //add more functionality 
        
        
        getline(cin, userChoiceStr);
        
        if(userChoiceStr != "quit")
        {
            int userChoice = stoi(userChoiceStr);

            switch (userChoice)
            {            
            case LOGIN:
                {
                    ChatWindow window(IPAddress, Port);

                    if(window.Login())
                    {
                        window.Chat();
                    }
                    else
                    {
                        cout<<endl<<"Max attempts reached... returning to main menu"<<endl;
                        //Chat session has ended or max number of tries exceeded. 
                    }

                    window.Disconnect();
                }
                break;
            
            default:
                cout<<"Invalid choice entered please try again."<<endl;
                break;
            }
        }

        //clear input buffer for next user input 
    }
}