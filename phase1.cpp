/*******************************************************************************
 * Phase1 Implementation                                                       *
 * For DeCODE   (COMP 11 Project 2 | 2016 Spring)                           *
 * modified by: Michael Edegware                                               *
 * Date: 4/23/2016                                                             *
 * Joke: Q. How can a man go eight days without sleep?                         *
 * A. He sleeps at night                                                       *
 ******************************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "keylist.h"
#include "cipher.h"
#include "dictionary.h"

// to make:
// clang++ -Wall -Wextra keylist.cpp phase1.cpp cipher.cpp -o phase1
using namespace std;

struct Arguments {
        string operation;
        string key_or_filename;
};
/////////////////// Function Definitions ///////////////////
void print_usage(string program_name);
Arguments check_arguments(int argc, char *argv[]);
void encrypt(string key);
void decrypt(string key);
void brute_force(string filename);
float percentage_calculator(string str);
int count_words(string str);
string read_input(string operation);
/////////////////// constant  ////////////////////////////
const int PERCENTAGE = 100;
const int TOP_PERCENTAGE = 5;
/////////////////// Function Code  ///////////////////
int main(int argc, char *argv[]) {
        Arguments args = check_arguments(argc, argv);
        if (args.operation == "none") {
                return -1; // bad argument list
        } else if (args.operation == "encrypt") {
                encrypt(args.key_or_filename);
        } else if (args.operation == "decrypt") {
                decrypt(args.key_or_filename);
        } else if (args.operation == "keyfile") {
                brute_force(args.key_or_filename);
        }
        return 0;
}

// check_arguments()
// Purpose: To parse the command line arguments
// Arguments: the command line arguments :)
// Return value: an Arguments struct with the
//               operation information and either
//               the key or filename
//               The operation will be "none" if
//               the usage was incorrect
Arguments check_arguments(int argc, char *argv[]) {
        Arguments args;
        args.operation = "none"; // no operation yet

        string program_name = argv[0];

        if (argc < 3) {
                print_usage(program_name);
        } else {
                string poss_op = argv[1]; // the first argument
                if (poss_op == "--encrypt") {
                        args.operation = "encrypt";
                        args.key_or_filename = argv[2];
                } else if (poss_op == "--decrypt") {
                        args.operation = "decrypt";
                        args.key_or_filename = argv[2];
                } else if (poss_op == "--keyfile") {
                        args.operation = "keyfile";
                        args.key_or_filename = argv[2];
                }
        }
        return args;
}

// print_usage()
// Purpose: to print the usage for the program
// Arguments: none
// Return value: none
void print_usage(string program_name) {
        cout << "Usage:" << endl << endl;
        cout << program_name << " --encrypt key" << endl << endl;
        cout << program_name << " --decrypt key" << endl << endl;
        cout << program_name << " --keyfile filename" << endl;
        cout << endl;
}

// encrypt()
// Purpose: to use the Cipher class to encrypt a string
// Arguments: the key to use for the encryption
// Return value: none
void encrypt(string key) {
        string plaintext = read_input("encrypt");
        Cipher cipher("encrypt", key, plaintext);
        cout << endl << "Ciphertext:" << endl;
        cout << cipher.get_ciphertext() << endl;
}

// decrypt()
// Purpose: to use the Cipher class to decrypt a string
// Arguments: the key to use for the decryption
// Return value: none
void decrypt(string key) {
        string ciphertext = read_input("decrypt");
        Cipher cipher("decrypt", key, ciphertext);
        cout << endl << "Plaintext:" << endl;
        cout << cipher.get_plaintext() << endl;
}

// brute_force()
// Purpose: to use the Cipher class and a keyfile to decrypt a string
// Arguments: the filename for the keyfile
// Return value: none
void brute_force(string filename) {
        KeyList k(filename);
        float percentage, a;
        string plaintext, ciphertext = read_input("decrypt");
        KeyWithResult kwr = k.next();
        cout << endl << "Checking:" << " ";
        while (true) {
                Cipher cipher("decrypt", kwr.key, ciphertext);
                cout << kwr.key << ","<< " ";
                plaintext = cipher.get_plaintext();
                percentage = percentage_calculator(plaintext);
                k.update_result(kwr.key, percentage, plaintext);
                if (kwr.word_percentage == -1) {
                         break;
                }
                kwr = k.next();
        }
        a = percentage;//saves the percentage
        k.reset_iterator();
        kwr = k.next();
        cout << endl << endl;
        cout << "Top 5 matches:" << endl;
        for (int i = 0; i < 100; i++) {
                cout << "'" << kwr.plaintext << "'"
                     << " decrypted with key ";
                cout << "'" << kwr.key << "'"<< ":";
                if (kwr.word_percentage == -1) {
                        cout << " " << a;
                } else {
                        cout << " " << kwr.word_percentage;
                }
                cout << "%" << endl;
                kwr = k.next();
        }
}
// read_input()
// Purpose: to read a line of input from the user
// Arguments: the operation to ask for (e.g., "encrypt" or "decrypt")
// Return value: the string that was returned
string read_input(string operation) {
        string text;
        cout << "Please enter text to " << operation << ":" << endl;
        getline(cin, text);
        return text;
}
// percentage_calculator()
// Purpose: to calculate the percentage of words in the dictionary
// Arguments: string
// Return value: percentage
float percentage_calculator(string str) {
        Dictionary d;
        int word_in_dictionary = 0;
        int slen = str.length();
        int word_count = count_words(str);
        string word = "";
        for (int i = 0; i < slen; i++) {
                if (str[i] != ' ') {
                        word += str[i];//check for word in a sentence
                } else if (str[i] == ' ' and str[i - 1] != ' ') {
                        if (d.has_word(word)) {
                                word_in_dictionary++;
                        }
                        word = "";
                }
        }//check for word at end of sentence
        if (str[str.length() - 1] != ' ') {
                if (d.has_word(word)) {
                        word_in_dictionary++;
                }
                word = "";
        }
        float c = PERCENTAGE * word_in_dictionary;
        float f = (c / word_count);
        return f;
}
// count_words()
// Purpose: to count the number of words in a sentence
// Arguments: string
// Return value: percentage
int count_words(string str) {
        int slen = str.length();
        int word_count = 0;
        for (int i = 0; i < slen; i++) {
                if (str[i] == ' ' and str[i - 1] != ' ') {
                        word_count++;
                }
        }
        //   check for last letter
        if (str[str.length() - 1] != ' ') {
                word_count++;
        }
        return word_count;
}
