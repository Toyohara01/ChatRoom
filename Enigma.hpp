//https://www.apprendre-en-ligne.net/crypto/bibliotheque/PDF/paperEnigma.pdf

/******************************************************************************
* Enigma.hpp                                                                  *
*   header file defining the Enigma class that will be used for both the      *
*   encryption and decryption of message strings.                             *
*                                                                             *
* Author: Lukas DeLong                                                        *
* Spring 2019                                                                 *
* SE420/SE310                                                                 *
*******************************************************************************/

#ifndef ENIGMA_HPP
#define ENIGMA_HPP

#include <iostream>

class Enigma
{
    private:
        char rotor1[26][2]={
            {'A', 'E'}, {'B', 'K'}, {'C', 'M'}, {'D', 'F'},
            {'E', 'L'}, {'F', 'G'}, {'G', 'D'}, {'H', 'Q'},
            {'I', 'V'}, {'J', 'Z'}, {'K', 'N'}, {'L', 'T'},
            {'M', 'O'}, {'N', 'W'}, {'O', 'Y'}, {'P', 'H'},
            {'Q', 'X'}, {'R', 'U'}, {'S', 'S'}, {'T', 'P'},
            {'U', 'A'}, {'V', 'I'}, {'W', 'B'}, {'X', 'R'},
            {'Y', 'C'}, {'Z', 'J'}
        };
                //NOTE: put initialization in constructor. LAD
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

        std::string plainText, cipherText;
        int key[3]={0, 0, 0};

    public:
        Enigma();
        int findIndex(char letter, int mode, int side=0, int refIdx=0);
        std::string Encrypt(std::string input);
        std::string Decrypt(std::string input);
        ~Enigma();
};

#endif //ENIGMA_HPP