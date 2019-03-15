
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
#include <iosetream>
#include <string>

using namespace std;

Enigma::Enigma()
{
    //NOTE: add code to compute key based on current date. LAD
}

int Enigma::findIndex(char letter, int mode, int side=0, int refIdx=0);
{
    //varaible for searching through array. LAD
    int arrayIdx = 0;

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
}

string Enigma::Decrypt(string input)
{

}

Enigma::~Enigma()
{
    
}