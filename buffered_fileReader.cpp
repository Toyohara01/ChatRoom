#include "buffered_fileReader.hpp"

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

// size_t buffered_fileReader::getNumberOfElements()
// {

// }

// // Stripe file over multiple disks
// char* stripeFile(char *inputFileName, int offsetSectors)
// {
// int fd[5], idx;
// FILE *fdin;
// unsigned char stripe[5*STRIP_SIZE];
// int offset = 0, bread = 0, btoread = (4*STRIP_SIZE), bwritten = 0, btowrite = (STRIP_SIZE), sectorCnt = 0, byteCnt = 0;

// //assert((fd[0] = file.open("Chatroom.txt", O_RDWR | O_CREAT, 0064)) != 0);
// }