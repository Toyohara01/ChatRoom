
/******************************************************************************
* Crypto.cpp                                                                  *
*   File containing the methods necessary for an Crypto object to perform     *
*   encryption and decryption on the strings passed to it                     *
*                                                                             *
* Author: Lukas DeLong                                                        *
* Spring 2019                                                                 *
* SE420/SE310                                                                 *
*******************************************************************************/
#include "Crypto.hpp"
#include <iostream>
#include <ctime>

using namespace std;

char Enigma::rotor1[26][2]=
{
    {'A', 'E'}, {'B', 'K'}, {'C', 'M'}, {'D', 'F'},
    {'E', 'L'}, {'F', 'G'}, {'G', 'D'}, {'H', 'Q'},
    {'I', 'V'}, {'J', 'Z'}, {'K', 'N'}, {'L', 'T'},
    {'M', 'O'}, {'N', 'W'}, {'O', 'Y'}, {'P', 'H'},
    {'Q', 'X'}, {'R', 'U'}, {'S', 'S'}, {'T', 'P'},
    {'U', 'A'}, {'V', 'I'}, {'W', 'B'}, {'X', 'R'},
    {'Y', 'C'}, {'Z', 'J'}
};
char Enigma::rotor2[26][2]=
{
    {'A', 'A'}, {'B', 'J'}, {'C', 'D'}, {'D', 'K'},
    {'E', 'S'}, {'F', 'I'}, {'G', 'R'}, {'H', 'U'},
    {'I', 'X'}, {'J', 'B'}, {'K', 'L'}, {'L', 'H'},
    {'M', 'W'}, {'N', 'T'}, {'O', 'M'}, {'P', 'C'},
    {'Q', 'Q'}, {'R', 'G'}, {'S', 'Z'}, {'T', 'N'},
    {'U', 'P'}, {'V', 'Y'}, {'W', 'F'}, {'X', 'V'},
    {'Y', 'O'}, {'Z', 'E'}
};

char Enigma::rotor3[26][2]=
{
    {'A', 'B'}, {'B', 'D'}, {'C', 'F'}, {'D', 'H'},
    {'E', 'J'}, {'F', 'L'}, {'G', 'C'}, {'H', 'P'},
    {'I', 'R'}, {'J', 'T'}, {'K', 'X'}, {'L', 'V'},
    {'M', 'Z'}, {'N', 'N'}, {'O', 'Y'}, {'P', 'E'},
    {'Q', 'I'}, {'R', 'W'}, {'S', 'G'}, {'T', 'A'},
    {'U', 'K'}, {'V', 'M'}, {'W', 'U'}, {'X', 'S'},
    {'Y', 'Q'}, {'Z', 'O'}
};

char Enigma::alphabet[26]=
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

char Enigma::reflector[26]=
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'D', 'I', 'J',
    'K', 'G', 'M', 'K', 'M', 'I', 'E', 'B', 'F', 'T',
    'C', 'V', 'V', 'J', 'A', 'T'
};

Enigma::Enigma()
{
    //find current time and date. LAD
    time_t currentDate = time(0);
    tm *lt = localtime(&currentDate);

    //create key based on day, month, and year. LAD
    key[0] = (lt->tm_year)%26;
    key[1] = (lt->tm_mon)%26;
    key[2] = (lt->tm_mday)%26;
}

int Enigma::findIndex(char letter, ROTOR mode, SIDE side, int refIdx)
{
    //mode determines what rotor to search through. LAD
    switch(mode)
    {
        //case 0 search through alphabet array. LAD
        case ALPHABET:
            //loop through the alphabet array to compare letters. LAD
            for(int arrayIdx=0;arrayIdx<26;arrayIdx++)
            {
                //if the current character being checked and input letter match. LAD
                if(alphabet[arrayIdx] == letter)
                {
                    //return the index. LAD
                    return(arrayIdx);
                }
            }
        break;
        //case 1 search through rotor1 array. LAD
        case FIRST_ROTOR:
            //loop through rotor1 array to compare letters. LAD
            for(int arrayIdx=0;arrayIdx<26;arrayIdx++)
            {
                //if current character being checked matches input letter. LAD
                if(rotor1[arrayIdx][side] == letter)
                {
                    //return the index. LAD
                    return(arrayIdx);
                }
            }
        break;
        //case 2 search through rotor2 array. LAD
        case SECOND_ROTOR:
            for(int arrayIdx=0;arrayIdx<26;arrayIdx++)
            {
                if(rotor2[arrayIdx][side] == letter)
                {
                    return(arrayIdx);
                }
            }
        break;
        //case 3 search through rotor3 array. LAD
        case THIRD_ROTOR:
            for(int arrayIdx=0;arrayIdx<26;arrayIdx++)
            {
                if(rotor3[arrayIdx][side] == letter)
                {
                    return(arrayIdx);
                }
            }
        break;
        //case 4 search through reflector array. LAD
        case REFLECTOR:
            //loop through the reflector array to compare letters. LAD
            for(int arrayIdx=0;arrayIdx<26;arrayIdx++)
            {
                //if the duplicate letter in the reflector has been found. LAD
                if(reflector[arrayIdx] == letter && arrayIdx != refIdx)
                {
                    //return the index. LAD
                    return(arrayIdx);
                }
            }
        break;
        //invalid input. LAD
        default:
            cout << "something went wrong with mode arguement." << endl; //NOTE: replace with actual error handling. LAD
            return(0);
        break;
    }

    return(0);
}

string Enigma::Encrypt(string input)    //NOTE: need to add rotor rotation stuff. LAD
{
    //define variables. LAD
    char tempChar;
    int tempIdx;
    string tempString;

    //loop through every character in the input string. LAD
    for(unsigned int i=0; i<input.length();i++)
    {
        //if the current character is a letter
        if(isalpha(input.at(i)))
        {
            //set tempChar to character currently being encrypted. LAD
            tempChar = toupper(input.at(i));

            //find tempChar's index in the alphabit. LAD
            tempIdx = Enigma::findIndex(tempChar, ALPHABET);

            //set tempChar to cooresponding character on right side of rotor1. LAD
            tempChar = rotor1[tempIdx][1];

            //find index for identical character on left side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, FIRST_ROTOR, LEFT);

            //set tempChar to cooresponding character on rightside of rotor2. LAD
            tempChar = rotor2[tempIdx][1];

            //find index for identical character on left side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, SECOND_ROTOR, LEFT);

            //set tempChar to cooresponding character on right side of rotor3. LAD
            tempChar = rotor3[tempIdx][1];

            //find index for identical character on left side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, THIRD_ROTOR, LEFT);

            //set tempChar to character in cooreponding position in relector. LAD
            tempChar = reflector[tempIdx];

            //find index of duplicate of tempChar on reflector. LAD
            tempIdx = Enigma::findIndex(tempChar, REFLECTOR, LEFT, tempIdx);

            //set tempChar to cooresponding character on left side of rotor3. LAD
            tempChar = rotor3[tempIdx][0];

            //find index for identical character on right side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, THIRD_ROTOR, RIGHT);

            //set tempChar to cooreponding character on left side of rotor2. LAD
            tempChar = rotor2[tempIdx][0];

            //find index for identical character on right side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, SECOND_ROTOR, RIGHT);

            //set tempChar to cooresponding character on left side of rotor1. LAD
            tempChar = rotor1[tempIdx][0];

            //find index for identical character on right side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, FIRST_ROTOR, RIGHT);

            //set tempChar to cooresponding character in alphabet. LAD
            tempChar = alphabet[tempIdx];

            //replace original character in input string with encrypted character. LAD
            input[i] = tempChar;
        }
        //if character being checked is a digit. LAD
        else if(isdigit(input.at(i)))
        {
            //leave it alone
        }
        //if the character is a space. LAD
        else if(input.at(i) == ' ')
        {
            input[i] = '*';
        }
        //otherwise it is not an alphanumeric character or a space
        else
        {
            //leave it alone
        }

        //rotate rotor1 up once. LAD
        key[2]++;

        //if rotor1 is set to above 25. LAD
        if(key[2]>25)
        {
            //reset rotor1 to 0. LAD
            key[2] = 0;

            //rotate rotor2 up once. LAD
            key[1]++;

            //if rotor2 is set above 25. LAD
            if(key[1>25])
            {
                //reset rotor2 to 0. LAD
                key[1] = 0;

                //rotate rotor3 up once. LAD
                key[0]++;

                //if rotor3 is set above 25. LAD
                if(key[0]>25)
                {
                    //reset rotor3 to 0. LAD
                    key[0] = 0;
                }
            }
        }
    }

    //set the ciperText field to the newly encrypted string. LAD
    cipherText = input;

    //return encypted message. LAD
    return(cipherText);
}

string Enigma::Decrypt(string input)
{
    //define variables. LAD
    char tempChar;
    int tempIdx, beginIdx;
    string tempString;

    //Find begining of the message
    beginIdx = input.find(':');

    //loop through every character in the input string. LAD
    for(unsigned int i=beginIdx; i<input.length();i++)
    {
        //if the current character is a letter
        if(isalpha(input.at(i)))
        {
            //set tempChar to character currently being decrypted. LAD
            tempChar = toupper(input.at(i));

            //find tempChar's index in the alphabit. LAD
            tempIdx = Enigma::findIndex(tempChar, ALPHABET);

            //set tempChar to cooresponding character on right side of rotor1. LAD
            tempChar = rotor1[tempIdx][1];

            //find index for identical character on left side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, FIRST_ROTOR, LEFT);

            //set tempChar to cooresponding character on rightside of rotor2. LAD
            tempChar = rotor2[tempIdx][1];

            //find index for identical character on left side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, SECOND_ROTOR, LEFT);

            //set tempChar to cooresponding character on right side of rotor3. LAD
            tempChar = rotor3[tempIdx][1];

            //find index for identical character on left side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, THIRD_ROTOR, LEFT);

            //set tempChar to character in cooreponding position in relector. LAD
            tempChar = reflector[tempIdx];

            //find index of duplicate of tempChar on reflector. LAD
            tempIdx = Enigma::findIndex(tempChar, REFLECTOR, LEFT, tempIdx);

            //set tempChar to cooresponding character on left side of rotor3. LAD
            tempChar = rotor3[tempIdx][0];

            //find index for identical character on right side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, THIRD_ROTOR, RIGHT);

            //set tempChar to cooreponding character on left side of rotor2. LAD
            tempChar = rotor2[tempIdx][0];

            //find index for identical character on right side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, SECOND_ROTOR, RIGHT);

            //set tempChar to cooresponding character on left side of rotor1. LAD
            tempChar = rotor1[tempIdx][0];

            //find index for identical character on right side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, FIRST_ROTOR, RIGHT);

            //set tempChar to cooresponding character in alphabet. LAD
            tempChar = alphabet[tempIdx];

            //replace original character in input string with decrypted character. LAD
            input[i] = tempChar;
        }
        //if character being checked is a digit. LAD
        else if(isdigit(input.at(i)))
        {

        }
        //if the character is a space. LAD
        else if(input.at(i) == '*')
        {
            input[i] = ' ';
        }
        //otherwise it is not an alphanumeric character
        else
        {
            //leave it alone
        }
        
        //rotate rotor1 up once. LAD
        key[2]++;

        //if rotor1 is set to above 25. LAD
        if(key[2]>25)
        {
            //reset rotor1 to 0. LAD
            key[2] = 0;

            //rotate rotor2 up once. LAD
            key[1]++;

            //if rotor2 is set above 25. LAD
            if(key[1>25])
            {
                //reset rotor2 to 0. LAD
                key[1] = 0;

                //rotate rotor3 up once. LAD
                key[0]++;

                //if rotor3 is set above 25. LAD
                if(key[0]>25)
                {
                    //reset rotor3 to 0. LAD
                    key[0] = 0;
                }
            }
        }
    }

    //set the plainText field to the newly decrypted string. LAD
    plainText = input;

    //return decrypted message
    return(plainText);    
}

std::string Enigma::callEncrypt(std::string input)
{
    //declare string to hold cipher text. LAD
    string encryptedText;    

    //call encrypt
    encryptedText = Encrypt(input);

    //return cipher text
    return(encryptedText);
}

std::string Enigma::callDecrypt(std::string input)
{
    //declare string to hold plain text
    string decryptedText;

    //call decrypt
    decryptedText = Decrypt(input);

    //return plaintext
    return(decryptedText);
}

Enigma::~Enigma()
{
}