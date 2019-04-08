// Arhive.cpp
// Description: Will be able to save and load strings and backup the statements through RAID
// system calls to read every x seconds to save 

#include "Archive.hpp"

// Archiving will put file / message into a destination
Archive::Archive()
{
	//archivedMessage = /*filepath*/message;

	cout << "File is being opened" << endl;
}


Archive::~Archive()
{
	cout << "File is being closed" << endl;
}

// Save the message into the arhive
void Archive::Save(string message)
{

	// open file 
	ofstream file("chatroom.txt", ios::app);

	if (file.is_open())
	{
		// open chatroom text and read and update file
		fopen("chatroom.txt", "r+");

		// store user message into file 
		file << message << endl;

		// Declaring argument for time() 
		time_t tt;

		// Declaring variable to store return value of 
		// localtime() 
		struct tm * ti;

		// Applying time() 
		time(&tt);

		// Using localtime() 
		ti = localtime(&tt);

		// Day Month Day Hour:Minute:Second Year
		file << asctime(ti) << endl;

		file.close();
	}
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
		// exit
	}

}

// Raid-5 encoding 
char* Archive::xorArchive(char *LBA1,
	char *LBA2,
	char *LBA3,
	char *LBA4,
	char *PLBA)
{
	int idx;

	for (idx = 0; idx < SECTOR_SIZE; idx++)
	{
		*(PLBA + idx) = (*(LBA1 + idx)) ^ (*(LBA2 + idx)) ^ (*(LBA3 + idx)) ^ (*(LBA4 + idx));
	}
}

// Raid-5 Rebuild
char* Archive::rebuildArchive(unsigned char *LBA1,
	unsigned char *LBA2,
	unsigned char *LBA3,
	unsigned char *PLBA,
	unsigned char *RLBA)
{
	int idx;
	unsigned char checkParity;

	for (idx = 0; idx<SECTOR_SIZE; idx++)
	{
		// Parity check word is simply XOR of remaining good LBAs
		checkParity = (*(LBA1 + idx)) ^ (*(LBA2 + idx)) ^ (*(LBA3 + idx));

		// Rebuilt LBA is simply XOR of original parity and parity check word
		// which will preserve original parity computed over the 4 LBAs
		*(RLBA + idx) = (*(PLBA + idx)) ^ (checkParity);
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
		cout << "Enter a message..." << endl;

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

	// pass username and pwd
	do {
		cout << "View messages(1), delete(2), archived(3), quit(4)" << endl;
		cin >> options;


		if (options == 1)
		{
			inputMessage.Load(msg);
		}
		else if (options == 2)
		{
			cout << "Messages deleted: " << endl;

			ofstream file;
			file.open("chatroom.txt", ofstream::trunc);
			file.close();
		}
		else if (options == 3)
		{
			cout << "Archived chats" << endl;

		}
	} while (options != 4);

}
