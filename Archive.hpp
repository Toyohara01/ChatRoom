#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <string.h>
#include <assert.h>

using namespace std;

#define SECTOR_SIZE (512)

#define STRIP_SIZE (1024)

#define MAX_LBAS (1000)

#define theMessages "#This is a test case string of 0123456789#"

#define NULL_RAID_STRING "#FFFFFFFFFFFFFFFF#"

#define PTR_CAST (char *)

static unsigned char testRebuild[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA1[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA2[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA3[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA4[MAX_LBAS][SECTOR_SIZE];

//char testPLBA[MAX_LBAS][SECTOR_SIZE];



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

};


#endif //ARCHIVE_HPP
