#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>

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

#endif //ARCHIVE_HPP
