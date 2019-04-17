//https://www.apprendre-en-ligne.net/crypto/bibliotheque/PDF/paperEnigma.pdf

/******************************************************************************
* Crypto.hpp                                                                  *
*   header file defining the Crypto class that will be used for both the      *
*   encryption and decryption of message strings.                             *
*                                                                             *
* Author: Lukas DeLong                                                        *
* Spring 2019                                                                 *
* SE420/SE310                                                                 *
*******************************************************************************/

#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include<string>

class Crypto
{
    protected:
        std::string plainText, cipherText;
        virtual std::string Encrypt(std::string input)=0;
        virtual std::string Decrypt(std::string input)=0;

    public:
        virtual std::string callEncrypt(std::string input)=0;
        virtual std::string callDecrypt(std::string input)=0;
};

class Enigma : public Crypto
{
    private:
        static char rotor1[26][2];
        static char rotor2[26][2];
        static char rotor3[26][2];
        static char alphabet[26];
        static char reflector[26];
        unsigned int key[3];
        
        std::string Encrypt(std::string input);
        std::string Decrypt(std::string input);
        int findIndex(char letter, int mode, int side=0, int refIdx=0);

    public:
        Enigma();
        std::string callEncrypt(std::string input);
        std::string callDecrypt(std::string input);
        ~Enigma();
};

#endif //CRYPTO_HPP