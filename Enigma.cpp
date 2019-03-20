
/******************************************************************************
* Enigma.cpp                                                                  *
*   File containing the methods necessary for an enigma object to perform     *
*   encryption and decryption on the strings passed to it                     *
*                                                                             *
* Author: Lukas DeLong                                                        *
* Spring 2019                                                                 *
* SE420/SE310                                                                 *
*******************************************************************************/

#include "Enigma.hpp"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

char rotor1[26][2]={
    {'A', 'E'}, {'B', 'K'}, {'C', 'M'}, {'D', 'F'},
    {'E', 'L'}, {'F', 'G'}, {'G', 'D'}, {'H', 'Q'},
    {'I', 'V'}, {'J', 'Z'}, {'K', 'N'}, {'L', 'T'},
    {'M', 'O'}, {'N', 'W'}, {'O', 'Y'}, {'P', 'H'},
    {'Q', 'X'}, {'R', 'U'}, {'S', 'S'}, {'T', 'P'},
    {'U', 'A'}, {'V', 'I'}, {'W', 'B'}, {'X', 'R'},
    {'Y', 'C'}, {'Z', 'J'}
};

char rotor2[26][2]={
    {'A', 'A'}, {'B', 'J'}, {'C', 'D'}, {'D', 'K'},
    {'E', 'S'}, {'F', 'I'}, {'G', 'R'}, {'H', 'U'},
    {'I', 'X'}, {'J', 'B'}, {'K', 'L'}, {'L', 'H'},
    {'M', 'W'}, {'N', 'T'}, {'O', 'M'}, {'P', 'C'},
    {'Q', 'Q'}, {'R', 'G'}, {'S', 'Z'}, {'T', 'N'},
    {'U', 'P'}, {'V', 'Y'}, {'W', 'F'}, {'X', 'V'},
    {'Y', 'O'}, {'Z', 'E'}
};

char rotor3[26][2]={
    {'A', 'B'}, {'B', 'D'}, {'C', 'F'}, {'D', 'H'},
    {'E', 'J'}, {'F', 'L'}, {'G', 'C'}, {'H', 'P'},
    {'I', 'R'}, {'J', 'T'}, {'K', 'X'}, {'L', 'V'},
    {'M', 'Z'}, {'N', 'N'}, {'O', 'Y'}, {'P', 'E'},
    {'Q', 'I'}, {'R', 'W'}, {'S', 'G'}, {'T', 'A'},
    {'U', 'K'}, {'V', 'M'}, {'W', 'U'}, {'X', 'S'},
    {'Y', 'Q'}, {'Z', 'O'}
};

char alphabet[26]={
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

char reflector[26]={
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

    cout << "Enigma object created!" << endl;
}

int Enigma::findIndex(char letter, int mode, int side, int refIdx)
{
    //varaible for searching through array. LAD
    int arrayIdx = 0;

    //mode determines what rotor to search through. LAD
    switch(mode)
    {
        //case 0 search through alphabet array. LAD
        case 0:
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
        case 1:
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
        case 2:
            for(int arrayIdx=0;arrayIdx<26;arrayIdx++)
            {
                if(rotor2[arrayIdx][side] == letter)
                {
                    return(arrayIdx);
                }
            }
        break;
        //case 3 search through rotor3 array. LAD
        case 3:
            for(int arrayIdx=0;arrayIdx<26;arrayIdx++)
            {
                if(rotor3[arrayIdx][side] == letter)
                {
                    return(arrayIdx);
                }
            }
        break;
        //case 4 search through reflector array. LAD
        case 4:
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
        break;
    }
}

string Enigma::Encrypt(string input)    //NOTE: need to add rotor rotation stuff. LAD
{
    //define variables. LAD
    char tempChar;
    int tempIdx, i;
    string tempString;

    //loop through every character in the input string. LAD
    for(int i=0; i<input.length();i++)
    {
        //if the current character is a letter
        if(isalpha(input.at(i)))
        {
            //set tempChar to character currently being encrypted. LAD
            tempChar = toupper(input.at(i));

            //find tempChar's index in the alphabit. LAD
            tempIdx = Enigma::findIndex(tempChar, 0);

            //set tempChar to cooresponding character on right side of rotor1. LAD
            tempChar = rotor1[tempIdx][1];

            //find index for identical character on left side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, 1, 0);

            //set tempChar to cooresponding character on rightside of rotor2. LAD
            tempChar = rotor2[tempIdx][1];

            //find index for identical character on left side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, 2, 0);

            //set tempChar to cooresponding character on right side of rotor3. LAD
            tempChar = rotor3[tempIdx][1];

            //find index for identical character on left side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, 3, 0);

            //set tempChar to character in cooreponding position in relector. LAD
            tempChar = reflector[tempIdx];

            //find index of duplicate of tempChar on reflector. LAD
            tempIdx = Enigma::findIndex(tempChar, 4, 0, tempIdx);

            //set tempChar to cooresponding character on left side of rotor3. LAD
            tempChar = rotor3[tempIdx][0];

            //find index for identical character on right side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, 3, 1);

            //set tempChar to cooreponding character on left side of rotor2. LAD
            tempChar = rotor2[tempIdx][0];

            //find index for identical character on right side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, 2, 1);

            //set tempChar to cooresponding character on left side of rotor1. LAD
            tempChar = rotor1[tempIdx][0];

            //find index for identical character on right side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, 1, 1);

            //set tempChar to cooresponding character in alphabet. LAD
            tempChar = alphabet[tempIdx];

            //replace original character in input string with encrypted character. LAD
            input[i] = tempChar;
        }
        //if character being checked is a digit. LAD
        else if(isdigit(input.at(i)))
        {

        }
        //otherwise if the character is not a letter or digit. LAD
        else
        {
            input[i] = '*';
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

    cout << cipherText << endl;

    //return encypted message. LAD
    return(cipherText);
}

string Enigma::Decrypt(string input)
{
    //define variables. LAD
    char tempChar;
    int tempIdx, i;
    string tempString;

    //loop through every character in the input string. LAD
    for(int i=0; i<input.length();i++)
    {
        //if the current character is a letter
        if(isalpha(input.at(i)))
        {
            //set tempChar to character currently being decrypted. LAD
            tempChar = toupper(input.at(i));

            //find tempChar's index in the alphabit. LAD
            tempIdx = Enigma::findIndex(tempChar, 0);

            //set tempChar to cooresponding character on right side of rotor1. LAD
            tempChar = rotor1[tempIdx][1];

            //find index for identical character on left side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, 1, 0);

            //set tempChar to cooresponding character on rightside of rotor2. LAD
            tempChar = rotor2[tempIdx][1];

            //find index for identical character on left side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, 2, 0);

            //set tempChar to cooresponding character on right side of rotor3. LAD
            tempChar = rotor3[tempIdx][1];

            //find index for identical character on left side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, 3, 0);

            //set tempChar to character in cooreponding position in relector. LAD
            tempChar = reflector[tempIdx];

            //find index of duplicate of tempChar on reflector. LAD
            tempIdx = Enigma::findIndex(tempChar, 4, 0, tempIdx);

            //set tempChar to cooresponding character on left side of rotor3. LAD
            tempChar = rotor3[tempIdx][0];

            //find index for identical character on right side of rotor3. LAD
            tempIdx = Enigma::findIndex(tempChar, 3, 1);

            //set tempChar to cooreponding character on left side of rotor2. LAD
            tempChar = rotor2[tempIdx][0];

            //find index for identical character on right side of rotor2. LAD
            tempIdx = Enigma::findIndex(tempChar, 2, 1);

            //set tempChar to cooresponding character on left side of rotor1. LAD
            tempChar = rotor1[tempIdx][0];

            //find index for identical character on right side of rotor1. LAD
            tempIdx = Enigma::findIndex(tempChar, 1, 1);

            //set tempChar to cooresponding character in alphabet. LAD
            tempChar = alphabet[tempIdx];

            //replace original character in input string with decrypted character. LAD
            input[i] = tempChar;
        }
        //if character being checked is a digit. LAD
        else if(isdigit(input.at(i)))
        {

        }
        //otherwise if the character is not a letter or digit. LAD
        else
        {
            input[i] = ' ';
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

    cout << plainText << endl;

    //return decrypted message
    return(plainText);    
}

Enigma::~Enigma()
{
    cout << "Enigma object destructed!" << endl;
}
