#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <string.h>
#include <assert.h>

#define SECTOR_SIZE (512)

#define STRIP_SIZE (1024)

#define MAX_LBAS (1000)

using namespace std;

class Archive
{
private:
	ofstream * file;

	// char* xorArchive(char *LBA1, 
	// char *LBA2, 
	// char *LBA3, 
	// char *LBA4, 
	// char *PLBA);

	// void rebuildArchive(unsigned char *LBA1,
	// unsigned char *LBA2,
	// unsigned char *LBA3,
	// unsigned char *PLBA,
	// unsigned char *RLBA);

public:
	Archive();
	void Save(string message);
	void Load(string message);
	~Archive();

	char* stripeFile(char *inputFileName, int offsetSectors);

	void xorArchive(char *LBA1,
		char *LBA2,
		char *LBA3,
		char *LBA4,
		char *PLBA);

	void rebuildArchive(char *LBA1,
		char *LBA2,
		char *LBA3,
		char *PLBA,
		char *RLBA);

	int checkEquiv(char *LBA1, char *LBA2);

	/******************************************************************************/
};


/******************************************************************************/

#endif //ARCHIVE_HPP
