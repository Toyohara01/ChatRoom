#include <iostream>
#include "Enigma.hpp"
#include "Enigma.cpp" 

using namespace std;

int main()
{
    //instantiate enigma objects
    Enigma encryptObj;
    Enigma decryptObj;

    //declare vairable for message
    string text;

    //prompt user for input
    cout << "Enter Message: ";
    getline(cin, text);

    //execute encyption method
    text = encryptObj.Encrypt(text);

    //execute decryption method
    decryptObj.Decrypt(text);
}