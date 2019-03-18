#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <iostream>
#include <fstream>

using namespace std;

class Archive 
{
	private:
		ofstream *file;

		char* Xor(char *LBA1, char *LBA2, char *LBA3, char *LBA4, char *PLBA);

	public:
		Archive(string filepath);
		void Save();
		void Load();
		void RAID();
		~Archive();
};

#endif //ARCHIVE_HPP
