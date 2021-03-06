#include "../../Archive.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

static unsigned char testRebuild[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA1[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA2[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA3[MAX_LBAS][SECTOR_SIZE];
static unsigned char testLBA4[MAX_LBAS][SECTOR_SIZE];

char testPLBA[MAX_LBAS][SECTOR_SIZE];


// print buffer
void printBuffer(char *bufferToPrint)
{
	int idx;

	for (idx = 0; idx < SECTOR_SIZE; idx++)
	{
		cout << bufferToPrint[idx];
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	int idx;
	Archive inputMessage;
	int loop = 1, options = 0;

	// array bounds
	string msg;

	// get messages
	do {
		cout << "Enter a message...(enter 'e' to exit)" << endl;

		// Get line with spaces
		getline(cin, msg);


		// User will exit message input, and continue to next screen
		if (msg == "e")
		{
			loop = 0;
		}
		
		// User will keep inputting messages
		else
		{
			// send message inputs to save
			inputMessage.Save(msg);
		}
	} while (loop == 1);

	// pass username and pwd
	do {
		cout << "View messages(1), delete(2), Quit(3)" << endl;
		cout << "PerformRAID-0(4)" << endl;
		cout << "PerformRaid-1(5)" << endl;
		cout << "PerformRAID-4(6)" << endl;
		cout << "PerformRAID-5(7)" << endl;
		cout << "CheckEquivalence(8)" << endl;
		cin >> options;

		// view messages
		if (options == 1)
		{
			inputMessage.Load(msg);
		}
		
		// delete all messages
		else if (options == 2)
		{
			cout << "Messages deleted: " << endl;

			ofstream file, file1;
			file.open("chatroom.txt", ofstream::trunc);
			file1.open("backupChatroom.txt", ofstream::trunc);
			file.close();
			file1.close();
		}
		
		// RAID-0
		else if (options == 4)
		{

		}

		// RAID-1
		else if (options == 5)
		{
			// TEST CASE #2 (COPY FILE)
			
			// copy contents to another file
			ifstream  src("chatroom.txt", std::ios::binary);
			ofstream  dst("backupChatroom.txt", std::ios::binary);

			// contents being placed in backup file
			dst << src.rdbuf();

			cout << "Disk 2 copied contents successfully" << endl;
			cout <<	"Original and backup now match" << endl;
		}
		
		// RAID-4
		else if (options == 6)
		{

		}
		
		// RAID-5
		else if (options == 7)
		{
			// set all test buffers
			for (idx = 0; idx<MAX_LBAS; idx++)
			{

				// need this to process "chatroom.txt" instead of "theMessages"
				// theMessages will be stored in testLBAN 
				memcpy(&testLBA1[idx], theMessages, SECTOR_SIZE);
				memcpy(&testLBA2[idx], theMessages, SECTOR_SIZE);
				memcpy(&testLBA3[idx], theMessages, SECTOR_SIZE);
				memcpy(&testLBA4[idx], theMessages, SECTOR_SIZE);
				memcpy(&testRebuild[idx], NULL_RAID_STRING, SECTOR_SIZE);

				// TEST CASE 1 (Ability to recover from data loss)
				
				// Computer XOR from 4 LBAs for RAID-5
				cout << "Test Case 1 - Functional RAID-5" << endl;
				inputMessage.xorArchive(PTR_CAST &testLBA1[0],
					PTR_CAST &testLBA2[0],
					PTR_CAST &testLBA3[0],
					PTR_CAST &testLBA4[0],
					PTR_CAST &testPLBA[0]);

				// Now rebuild LBA into test to verify
				inputMessage.rebuildArchive(PTR_CAST &testLBA1[0],
					PTR_CAST &testLBA2[0],
					PTR_CAST &testLBA3[0],
					PTR_CAST &testLBA4[0],
					PTR_CAST &testRebuild[0]);

				cout << "LBA 4= " << endl;
				printBuffer((char *)&testLBA4[0]);
				getchar();

				cout << "Recovered LBA 4= " << endl;
				printBuffer((char *)&testRebuild[0]);
				getchar();

				assert(memcmp(testRebuild, testLBA4, SECTOR_SIZE) != 0);
			}			
		}
		
		// Check Equivalence of Files
		else if (options == 8)
		{
/******************************************************************************/
			string file1, file2;
			ifstream chatroomFile1, chatroomFile2;

			file1 = "chatroom.txt";
			file2 = "backupChatroom.txt";

			//c_str() returns C-style string pointer
			chatroomFile1.open(file1.c_str(), ios::binary);
			chatroomFile2.open(file2.c_str(), ios::binary);

			// Error statements in case files do not open
			if (!chatroomFile1)
			{
				cout << "Couldn't open the file  " << file1 << endl;
				return 1;
			}

			if (!chatroomFile2)
			{
				cout << "Couldn't open the file " << file2 << endl;
				return 1;
			}

			// Compare number of lines in both files 
			int compare1, compare2;

			compare1 = 0;
			compare2 = 0;
			string str;

			// Get contents in file1 until the end-of-file
			while (!chatroomFile1.eof())
			{
				getline(chatroomFile1, str);
				compare1++;
			}

			// Get contents in file2 until the end-of-file
			while (!chatroomFile2.eof())
			{
				getline(chatroomFile2, str);
				compare2++;
			}


			chatroomFile1.clear();
			chatroomFile1.seekg(0, ios::beg);

			chatroomFile2.clear();
			chatroomFile2.seekg(0, ios::beg);

			// If the files do not match show user witch lines do not
			if (compare1 != compare2)
			{
				cout << "The files have a different number of lines" << endl;
				cout << file1 << " has " << compare1 << " lines and " <<
					file2 << " has " << compare2 << " lines" << endl;
				//return 1;
			}

			// Compare two files line by line
			char string1[512], string2[512];
			int j = 0, error_count = 0;


			while (!chatroomFile1.eof())
			{
				chatroomFile1.getline(string1, 512);
				chatroomFile2.getline(string2, 512);
				j++;
				if (strcmp(string1, string2) != 0)
				{
					cout << j << "-the strings are not equal " << endl;
					cout << " file1   " << string1 << endl;
					cout << " file2:  " << string2 << endl;
					error_count++;
				}
			}

			if (error_count > 0)
			{
				cout << "The two disks are different" << endl;
			}
			else
			{
				cout << "Disks match" << endl;
			}
/******************************************************************************/			
		}
	} while (options != 3);
}