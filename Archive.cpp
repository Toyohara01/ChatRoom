// Arhive.cpp
// Description: Will be able to save and load strings and backup the statements through RAID
// system calls to read every x seconds to save 

#include "Archive.hpp"

/******************************************************************************/
class buffered_fileReader
{
private:

	// member vairables for reading the file
	ifstream m_fs;
	size_t m_fileSize;
	string m_path; // idk

				   // member variables to work on the file
	size_t m_bufferSize;
	size_t m_elements; // number of elements in buffers
	size_t m_loadedElements;
	size_t m_globalAddress;

public:
	buffered_fileReader();
	buffered_fileReader(string path, size_t size);

	// getter for buffers
	size_t getNumberOfElements();
	size_t getBufferSize();
	char *getBuffer();
};

buffered_fileReader::buffered_fileReader()
{

}

// initial values are set
buffered_fileReader::buffered_fileReader(string path, size_t size)
{
	m_fs.open("chatroom.txt", ifstream::in | ifstream::binary);

	if (!(m_fs))
	{
		cerr << "Coudn't open file: " << "chatroom.txt" << endl;
	}

	// get file size
	m_fs.seekg(0, m_fs.end);
	m_fileSize = m_fs.tellg();
	m_fs.seekg(0, m_fs.beg);


}

size_t buffered_fileReader::getNumberOfElements()
{

}
/******************************************************************************/

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

/******************************************************************************/
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

//
// parity bits: odd # of 1's = 1, even # of 1's = 0
//

// Raid-5 Rebuild
char* Archive::rebuildArchive(unsigned char *LBA1,
	unsigned char *LBA2,
	unsigned char *LBA3,
	unsigned char *PLBA,
	unsigned char *RLBA)
{
	unsigned char checkParity;

	for (int idx = 0; idx<SECTOR_SIZE; idx++)
	{
		// Parity check word is simply XOR of remaining good LBAs
		checkParity = (*(LBA1 + idx)) ^ (*(LBA2 + idx)) ^ (*(LBA3 + idx));

		// Rebuilt LBA is simply XOR of original parity and parity check word
		// which will preserve original parity computed over the 4 LBAs
		*(RLBA + idx) = (*(PLBA + idx)) ^ (checkParity);
	}
}
/******************************************************************************/

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

			ofstream file, file1;
			file.open("chatroom.txt", ofstream::trunc);
			file1.open("backupChatroom.txt", ofstream::trunc);
			file.close();
			file1.close();
		}
		else if (options == 3)
		{

			// copy contents to another file
			ifstream  src("chatroom.txt", std::ios::binary);
			ofstream  dst("backupChatroom.txt", std::ios::binary);

			dst << src.rdbuf();

			cout << "Archived successfully" << endl;
		}

		else if (options == 5)
		{
			string file1, file2;
			ifstream Mary1, Mary2;

			file1 = "chatroom.txt";
			file2 = "backupChatroom.txt";

			Mary1.open(file1.c_str(), ios::binary); //c_str() returns C-style string pointer
			Mary2.open(file2.c_str(), ios::binary);

			if (!Mary1)
			{
				cout << "Couldn't open the file  " << file1 << endl;
				return 1;
			}

			if (!Mary2)
			{
				cout << "Couldn't open the file " << file2 << endl;
				return 1;
			}

			//---------- compare number of lines in both files ------------------//
			int c1, c2;
			c1 = 0;
			c2 = 0;
			string str;
			while (!Mary1.eof())
			{
				getline(Mary1, str);
				c1++;
			}
			//    Mary1.clear();   //  set new value for error control state  //
			//    Mary2.seekg(0,ios::beg);

			while (!Mary2.eof())
			{
				getline(Mary2, str);
				c2++;
			}

			Mary1.clear();  //add
			Mary1.seekg(0, ios::beg);  //add

			Mary2.clear();
			Mary2.seekg(0, ios::beg);

			if (c1 != c2)
			{
				cout << "Different number of lines in files!" << "\n";
				cout << file1 << " has " << c1 << " lines and " << file2 << " has" << c2 << " lines" << "\n";
				return 1;
			}

			//---------- compare two files line by line ------------------//
			char string1[256], string2[256];
			int j = 0, error_count = 0;
			while (!Mary1.eof())
			{
				Mary1.getline(string1, 256);
				Mary2.getline(string2, 256);
				j++;
				if (strcmp(string1, string2) != 0)
				{
					cout << j << "-the strings are not equal " << endl;
					cout << " file1   " << string1 << endl;
					cout << " file2:  " << string2 << endl;
					error_count++;
				}
			}
			if (error_count > 0) {
				cout << "files are diffrent" << endl;
			}
			else { cout << "files are the same" << endl; }

		}

	} while (options != 4);

}
