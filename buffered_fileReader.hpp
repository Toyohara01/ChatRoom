#ifndef BUFFERED_FILEREADER_HPP
#define BUFFERED_FILEREADER_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <string.h>
#include <assert.h>


using namespace std;
class buffered_fileReader
{
private:

	// member vairables for reading the file
	ifstream m_fs;
	size_t m_fileSize;
	string m_path;

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

#endif
