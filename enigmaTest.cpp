#include <iostream>
#include <random>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Crypto.hpp"
#include "Crypto.cpp" 

using namespace std;

void gen_random(char *s, const int len);

int main()
{
    //instantiate enigma objects
    Enigma encryptObj;
    Enigma decryptObj;

    //declare variables
    string encText, decText;
    char testText[2048];
    int pass=0, fail=0, testNum=0, i=0;
    double avgTime=0;
    
    cout << "Enter number of tests: ";
    cin >> testNum;

    for(i=0;i<testNum;i++)
    {
        gen_random(testText, 2047);

        cout << "Test text is: " << testText << endl << endl;

        clock_t start = clock();

        //encrypt string and display ciphertext
        encText = encryptObj.callEncrypt(testText);
        cout << "Encrypted text is: " + encText << endl << endl;

        //decrypt string and display plaintext
        decText = decryptObj.callDecrypt(encText);
        cout << "Decrypted text is: " + decText << endl << endl;

        clock_t end = clock();

        avgTime = (avgTime + double(end - start))/CLOCKS_PER_SEC;

        //if the input string is not equal to the decrypted string
        if(testText != decText)
        {
            fail++;
        }
        //otherwise the strings are equal to eachother
        else
        {
            pass++;
        }
    }

    avgTime = avgTime/testNum;

    cout << pass << " successes" << endl;
    cout << fail << " failures" << endl;
    cout << "Average time(s) to execute: " << avgTime << endl;
}

void gen_random(char *s, const int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}