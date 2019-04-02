// Arhive.cpp
// Description: Will be able to save and load strings and backup the statements through RAID
// system calls to read every x seconds to save 

//#include "Archive.hpp"

/******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#define SECTOR_SIZE 512

using namespace std;

class Archive
{
private:
	ofstream * file;

	char* Xor(char *LBA1, char *LBA2, char *LBA3, char *LBA4, char *PLBA);

public:
	Archive(/*string filepath*/);
	void Save(string message);
	void Load(string message);
	void RAID();
	~Archive();
};
/******************************************************************************/
// Arhiving will put file / message into a destination
Archive::Archive(/*string filepath */)
{
	//archivedMessage = /*filepath*/message;

}


Archive::~Archive()
{

}

// Save the message into the arhive
void Archive::Save(string message)
{
	// string savedMessage;
	// cin >> savedMessage;

	// put message into a file
	ofstream file("chatroom.txt", ios::app);

	// if (file.is_open())
	// {
	// file.open("chatroom.txt", ios::in);
	/******************************************************************************/
	// open chatroom text and read and update file
	fopen("chatroom.txt", "r");
	/******************************************************************************/
	file << message;
	file.close();
	// }
}

// load a message from the arhived file space
void Archive::Load(string message)
{

	cout << "Loaded File:" << endl;

	ifstream file("chatroom.txt", ios_base::in);

	if (file.is_open())
	{
		while (getline(file, message))
		{
			cout << message << endl;
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file";
	}

}


void Archive::RAID()
{

}

char* Archive::Xor(char *LBA1, char *LBA2, char *LBA3, char *LBA4, char *PLBA)
{
	int idx;

	for (idx = 0; idx < SECTOR_SIZE; idx++)
	{
		*(PLBA + idx) = (*(LBA1 + idx)) ^ (*(LBA2 + idx)) ^ (*(LBA3 + idx)) ^ (*(LBA4 + idx));
	}
}

int main()
{
	Archive inputMessage;
	int loop = 1, options = 0;

	// array bounds
	string msg;

	// get messages
	do {
		cout << "Message with no spaces" << endl;

		// Get line with spaces
		getline(cin, msg);

		if (msg == "exit")
		{
			loop = 0;
		}
		else
		{
			inputMessage.Save(msg);
		}
	} while (loop == 1);

	cout << "View messages(1), delete(2), archived(3)" << endl;
	cin >> options;

	if (options == 1)
	{
		inputMessage.Load(msg);
	}
	else if (options == 2)
	{
		cout << "Messages deleted: " << endl;
	}
	else
	{
		cout << "Archived chats" << endl;
	}
}
