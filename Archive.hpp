#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <string.h>

#define SECTOR_SIZE (512)

using namespace std;

class Archive
{
private:
	ofstream * file;

	char* xorArchive(char *LBA1,
		char *LBA2,
		char *LBA3,
		char *LBA4,
		char *PLBA);

	char* rebuildArchive(unsigned char *LBA1,
		unsigned char *LBA2,
		unsigned char *LBA3,
		unsigned char *PLBA,
		unsigned char *RLBA);

public:
	Archive();
	void Save(string message);
	void Load(string message);
	~Archive();

	/******************************************************************************/
};


/******************************************************************************/

#endif //ARCHIVE_HPP
