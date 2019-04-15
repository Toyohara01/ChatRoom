#include <iostream>
#include <random>
#include <cstdlib>
#include <string>
#include "Crypto.hpp"
#include "Crypto.cpp" 

using namespace std;

int main()
{
    //instantiate enigma objects
    Enigma encryptObj;
    Enigma decryptObj;

    //declare variables
    string userText, encText, decText;
    int pass=0, fail=0;

    cout << "Enter string you want to test: ";
    getline(cin, userText);

    //encrypt string and display ciphertext
    encText = encryptObj.callEncrypt(userText);
    cout << "Encrypted text is: " + encText << endl;

    //decrypt string and display plaintext
    decText = decryptObj.callDecrypt(encText);
    cout << "Decrypted text is: " + decText << endl;

    //if the input string is not equal to the decrypted string
    if(userText != decText)
    {
        fail++;
    }
    //otherwise the strings are equal to eachother
    else
    {
        pass++;
    }
    
    cout << pass << " successes" << endl;
    cout << fail << " failures" << endl;
}