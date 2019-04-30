// Arhive.cpp
// Description: Will be able to save and load strings and backup the statements through RAID
// system calls to read every x seconds to save 

#include "Archive.hpp"


// Archiving will put file / message into a destination
Archive::Archive()
{
	//archivedMessage = /*filepath*/message;
	//cout << "File is being opened" << endl;
}

// Archive destructor
Archive::~Archive()
{
	//cout << "File is being closed" << endl;
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

		// Display time: weekDay Month Day Hour:Minute:Second Year
		file << asctime(ti) << endl;

		// all data inserted into file, now close
		file.close();
	}
}

// load a message from the arhived file space
void Archive::Load(string message)
{

	cout << "Chat History:" << endl;

	// open file for viewing
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

/**********************************RAID****************************************/
// Raid-5 encoding 
void Archive::xorArchive(char *LBA1,
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

//
// parity bits: odd # of 1's = 1, even # of 1's = 0
//

// Raid-5 Rebuild
void Archive::rebuildArchive(char *LBA1,
	char *LBA2,
	char *LBA3,
	char *PLBA,
	char *RLBA)
{
	int idx;
	/*unsigned*/ char checkParity;

	for (idx = 0; idx<SECTOR_SIZE; idx++)
	{
		// Parity check word is simply XOR of remaining good LBAs
		checkParity = (*(LBA1 + idx)) ^ (*(LBA2 + idx)) ^ (*(LBA3 + idx));

		// Rebuilt LBA is simply XOR of original parity and parity check word
		// which will preserve original parity computed over the 4 LBAs
		*(RLBA + idx) = (*(PLBA + idx)) ^ (checkParity);
	}
}

// Check disk equivalence
int checkEquiv(char *LBA1, char *LBA2)
{
	int idx;

	for (idx = 0; idx<SECTOR_SIZE; idx++)
	{
		if ((*(LBA1 + idx)) != (*(LBA2 + idx)))
		{
			cout << "Equivalence check mismatch at byte " << idx << ": LBA1=0x" << (*LBA1 + idx) << ", LBA2=0x" << ((*LBA2 + idx)) << endl;
		}
	}
	return idx;
}

// // print buffer
// void printBuffer(char *bufferToPrint)
// {
// int idx;

// for(idx=0; idx < SECTOR_SIZE; idx++)
// {
// cout << bufferToPrint[idx];
// }
// cout << endl;
// }

/******************************************************************************/
// int main()
// {
// }