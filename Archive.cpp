// Arhive.cpp
// Description: Will be able to save and load strings and backup the statements through RAID
// system calls to read every x seconds to save 

#include "Archive.hpp"

// Arhiving will put file / message into a destination
Archive::Archive(string filepath)
{
	string arhivedMessage;
}


Archive::~Archive()
{

}

// Save the message into the arhive
void Archive::Save()
{
	string savedMessage;
	cin >> message;


}

// load a message from the arhived file space
void Archive::Load()
{
	string loadMesasge;

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

/*int main()
{


}  */