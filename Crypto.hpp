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
        static constexpr char rotor1[26][2]=
        {
            {'A', 'E'}, {'B', 'K'}, {'C', 'M'}, {'D', 'F'},
            {'E', 'L'}, {'F', 'G'}, {'G', 'D'}, {'H', 'Q'},
            {'I', 'V'}, {'J', 'Z'}, {'K', 'N'}, {'L', 'T'},
            {'M', 'O'}, {'N', 'W'}, {'O', 'Y'}, {'P', 'H'},
            {'Q', 'X'}, {'R', 'U'}, {'S', 'S'}, {'T', 'P'},
            {'U', 'A'}, {'V', 'I'}, {'W', 'B'}, {'X', 'R'},
            {'Y', 'C'}, {'Z', 'J'}
        };
        static constexpr char rotor2[26][2]=
        {
            {'A', 'A'}, {'B', 'J'}, {'C', 'D'}, {'D', 'K'},
            {'E', 'S'}, {'F', 'I'}, {'G', 'R'}, {'H', 'U'},
            {'I', 'X'}, {'J', 'B'}, {'K', 'L'}, {'L', 'H'},
            {'M', 'W'}, {'N', 'T'}, {'O', 'M'}, {'P', 'C'},
            {'Q', 'Q'}, {'R', 'G'}, {'S', 'Z'}, {'T', 'N'},
            {'U', 'P'}, {'V', 'Y'}, {'W', 'F'}, {'X', 'V'},
            {'Y', 'O'}, {'Z', 'E'}
        };
        static constexpr char rotor3[26][2]=
        {
            {'A', 'B'}, {'B', 'D'}, {'C', 'F'}, {'D', 'H'},
            {'E', 'J'}, {'F', 'L'}, {'G', 'C'}, {'H', 'P'},
            {'I', 'R'}, {'J', 'T'}, {'K', 'X'}, {'L', 'V'},
            {'M', 'Z'}, {'N', 'N'}, {'O', 'Y'}, {'P', 'E'},
            {'Q', 'I'}, {'R', 'W'}, {'S', 'G'}, {'T', 'A'},
            {'U', 'K'}, {'V', 'M'}, {'W', 'U'}, {'X', 'S'},
            {'Y', 'Q'}, {'Z', 'O'}
        };
        static constexpr char alphabet[26]=
        {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
            'U', 'V', 'W', 'X', 'Y', 'Z'
        };
        static constexpr char reflector[26]=
        {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'D', 'I', 'J',
            'K', 'G', 'M', 'K', 'M', 'I', 'E', 'B', 'F', 'T',
            'C', 'V', 'V', 'J', 'A', 'T'
        };
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