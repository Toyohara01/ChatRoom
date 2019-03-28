#include <iostream>
#include "Enigma.hpp"
#include "Enigma.cpp" 

using namespace std;

int main()
{
    //instantiate enigma objects
    Enigma encryptObj;
    Enigma decryptObj;

    //declare vairables
    string plainString, cipherString;
    int testNum, i, ii, randIndex, randSize;
    char characters[37] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', ' '
    };

    //prompt user for input
    cout << "Enter desired number of test runs: ";
    getline(cin, testNum);

    //loop to run desired number of test cases
    for(i=0;i<testNum;i++)
    {
        //fill each element of the string with a random character 
        for(ii=0;ii<256;ii++)
        {
            //generate random number
            randIndex = rand()%38;

            plainString[ii] = characters[randIndex];

        }

        //print plaintext string generated
        cout << plainString << endl;

        //encrypt plain text string
        cipherString = encryptObj.Encrypt(plainString);

        //print out ciphertext string
        cout << cipherString << endl;
    }
}