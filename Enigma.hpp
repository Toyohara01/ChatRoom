#ifndef ENIGMA_HPP
#define ENIGMA_HPP

#include <iostream>
#include <string>

using namespace std;

class Enigma
{
    private:
    // Insert different encryption methods, structures, rotors, vars, etc. Assing methods to someone

    public:
    Enigma();
	string Encrypt(string input);
	string Decrypt(string input);
    ~Enigma();
};

#endif //ENIGMA_HPP
