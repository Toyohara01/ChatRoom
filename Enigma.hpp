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
        std::string plainText, cipherText;
        int key[3];

    public:
        Enigma();
        int findIndex(char letter, int mode, int side=0, int refIdx=0);
        std::string Encrypt(std::string input);
        std::string Decrypt(std::string input);
        ~Enigma();
};

#endif //ENIGMA_HPP