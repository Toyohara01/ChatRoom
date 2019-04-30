#include "ChatWindow.hpp"
#include "Archive.hpp"

int main(int argc, char** argv)
{
    enum menuChoices {LOGIN = 1, 
					CHATHISTORY = 2,
					DELETE = 3,
					RAID0 = 4,
					RAID1 = 5,
					RAID4 = 6,
					RAID5 = 7,
					EQUIV = 8};
					
    vector<class Message> messages;
    messages.clear();
    string userChoiceStr;

    // Get IP Address and port of server to connect to. 
    string IPAddress = "127.0.0.1";
    uint16_t Port = 55500; //Hardcode for initial connection then reassign once connection is made 
   

    //Add logic for menu. 
    while(userChoiceStr != "quit")
    {
        cout <<"Menu:"<<endl<<"1) Login to chatroom"<<endl;
		cout <<"2) View previous Messages"<<endl;
		cout <<"3) Delete Messages"<<endl;
		cout <<"4) PerformRAID-0"<<endl;
		cout <<"5)PerformRaid-1" << endl;
		cout <<"6)PerformRAID-4" << endl;
		cout <<"7)PerformRAID-5" << endl;
		cout <<"8)CheckEquivalence" << endl;//add more functionality 
        
        
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
			case CHATHISTORY:
				{
					inputMessage.Load(msg);
				}
			case DELETE:
				{
					cout << "Messages deleted: " << endl;
					ofstream file, file1;
					file.open("chatroom.txt", ofstream::trunc);
					file1.open("backupChatroom.txt", ofstream::trunc);
					file.close();
					file1.close();
				}
			case RAID0:
				{
					
				}
			case RAID1:
				{
					// TEST CASE #2 (COPY FILE)
					
					// copy contents to another file
					ifstream  src("chatroom.txt", std::ios::binary);
					ofstream  dst("backupChatroom.txt", std::ios::binary);

					// contents being placed in backup file
					dst << src.rdbuf();

					cout << "Disk 2 copied contents successfully" << endl;
					cout <<	"Original and backup now match" << endl;					
				}
			case RAID4:
				{
					
				}
			case RAID5:
				{
					// set all test buffers
					for (idx = 0; idx<MAX_LBAS; idx++)
					{

						// need this to process "chatroom.txt" instead of "theMessages"
						// theMessages will be stored in testLBAN 
						memcpy(&testLBA1[idx], theMessages, SECTOR_SIZE);
						memcpy(&testLBA2[idx], theMessages, SECTOR_SIZE);
						memcpy(&testLBA3[idx], theMessages, SECTOR_SIZE);
						memcpy(&testLBA4[idx], theMessages, SECTOR_SIZE);
						memcpy(&testRebuild[idx], NULL_RAID_STRING, SECTOR_SIZE);

						// TEST CASE 1 (Ability to recover from data loss)
						
						// Computer XOR from 4 LBAs for RAID-5
						cout << "Test Case 1 - Functional RAID-5" << endl;
						inputMessage.xorArchive(PTR_CAST &testLBA1[0],
							PTR_CAST &testLBA2[0],
							PTR_CAST &testLBA3[0],
							PTR_CAST &testLBA4[0],
							PTR_CAST &testPLBA[0]);

						// Now rebuild LBA into test to verify
						inputMessage.rebuildArchive(PTR_CAST &testLBA1[0],
							PTR_CAST &testLBA2[0],
							PTR_CAST &testLBA3[0],
							PTR_CAST &testLBA4[0],
							PTR_CAST &testRebuild[0]);

						cout << "LBA 4= " << endl;
						printBuffer((char *)&testLBA4[0]);
						getchar();

						cout << "Recovered LBA 4= " << endl;
						printBuffer((char *)&testRebuild[0]);
						getchar();

						assert(memcmp(testRebuild, testLBA4, SECTOR_SIZE) != 0);					
					}
			case EQUIV:
				{
					string file1, file2;
					ifstream chatroomFile1, chatroomFile2;

					file1 = "chatroom.txt";
					file2 = "backupChatroom.txt";

					//c_str() returns C-style string pointer
					chatroomFile1.open(file1.c_str(), ios::binary);
					chatroomFile2.open(file2.c_str(), ios::binary);

					// Error statements in case files do not open
					if (!chatroomFile1)
					{
						cout << "Couldn't open the file  " << file1 << endl;
						return 1;
					}

					if (!chatroomFile2)
					{
						cout << "Couldn't open the file " << file2 << endl;
						return 1;
					}

					// Compare number of lines in both files 
					int compare1, compare2;

					compare1 = 0;
					compare2 = 0;
					string str;

					// Get contents in file1 until the end-of-file
					while (!chatroomFile1.eof())
					{
						getline(chatroomFile1, str);
						compare1++;
					}

					// Get contents in file2 until the end-of-file
					while (!chatroomFile2.eof())
					{
						getline(chatroomFile2, str);
						compare2++;
					}


					chatroomFile1.clear();
					chatroomFile1.seekg(0, ios::beg);

					chatroomFile2.clear();
					chatroomFile2.seekg(0, ios::beg);

					// If the files do not match show user witch lines do not
					if (compare1 != compare2)
					{
						cout << "The files have a different number of lines" << endl;
						cout << file1 << " has " << compare1 << " lines and " <<
							file2 << " has " << compare2 << " lines" << endl;
						//return 1;
					}

					// Compare two files line by line
					char string1[512], string2[512];
					int j = 0, error_count = 0;


					while (!chatroomFile1.eof())
					{
						chatroomFile1.getline(string1, 512);
						chatroomFile2.getline(string2, 512);
						j++;
						if (strcmp(string1, string2) != 0)
						{
							cout << j << "-the strings are not equal " << endl;
							cout << " file1   " << string1 << endl;
							cout << " file2:  " << string2 << endl;
							error_count++;
						}
					}

					if (error_count > 0)
					{
						cout << "The two disks are different" << endl;
					}
					else
					{
						cout << "Disks match" << endl;
					}					
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