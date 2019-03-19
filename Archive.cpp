// Arhive.cpp
// Description: Will be able to save and load strings and backup the statements through RAID

#include "Archive.hpp"

Archive::Archive(string filepath)
{

}

Archive::~Archive()
{

}

void Archive::Save()
{
	string message;
}

void Archive::Load()
{

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