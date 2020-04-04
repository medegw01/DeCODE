#include<iostream>
#include "keylist.h"
#include "cipher.h"

// to make:
// clang++ -Wall -Wextra keylist.cpp keylist_tester.cpp cipher.cpp -o keylist_tester
using namespace std;

const string KEYFILE = "10Passwords.txt";
const string TEST_CIPHERTEXT = "iscets__soaxiey__mrth_st";
int main()
{
        KeyList k(KEYFILE);
        KeyWithResult kwr = k.next();
        while(kwr.word_percentage != -1) {
                cout << kwr.key << endl;
                Cipher cipher("decrypt",kwr.key,TEST_CIPHERTEXT);
                cout << "\t" << cipher.get_plaintext() << endl;
                kwr = k.next();
        }
        return 0;
}

+++++++++

