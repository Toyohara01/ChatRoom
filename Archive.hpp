#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

class Archive 
{
private:
    char* Xor(char *LBA1, char *LBA2, char *LBA3, char *LBA4, char *PLBA);

public:
    Archive();
	void Save();
	void Load();
	void RAID();
    ~Archive();
};

#endif //ARCHIVE_HPP
