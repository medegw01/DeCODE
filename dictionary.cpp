
/*******************************************************************************
 * KeyList Class Implementation and for sorting list of word search            *
 * For DeCODE    (COMP 11 Project 2 | 2016 Spring)                             *
 * written by: Michael Edegware                                                *
 * Date: 4/18/2016                                                             *
 * Joke: Q. How can a man go eight days without sleep?                         *
 * A. He sleeps at night                                                       *
 ******************************************************************************/
#include "dictionary.h"
#include <fstream>

using namespace std;
// constructor calls read_dict_from_file()
// with the filename
Dictionary::Dictionary() // constructor
{
        num_elements = 0;
        capacity = CAPACITY;
        wordlist = new string[capacity];
        for (int i = 0; i < capacity; i++) {
                wordlist[i] = BLANK;
        }
        read_dict_from_file(DICT_FILE);
}
Dictionary::~Dictionary() // desctructor
{
        delete[] wordlist;
}
// read_dict_from_file()
// Purpose: Read the words in from the file
// Arguments: none
// Return value: none
// Note: WORDFILE holds a path to the list file
void Dictionary::read_dict_from_file(string filename) {
        ifstream word_file;
        string next_word;
        word_file.open(filename.c_str());
        while (getline(word_file, next_word)) {
                wordlist[num_elements] = next_word;
                num_elements++;
                if (num_elements == capacity) {
                        expand();
                }
        }
}
// expand function for dynamic array
void Dictionary::expand() {
        string *temp = new string[capacity * 2];
        for (int i = 0; i < capacity; i++) {
                temp[i] = wordlist[i];
        }
        delete[] wordlist;
        wordlist = temp;
        capacity *= 2;
}
// has_word()
// Purpose: search for the word in the dictionary
// Argument: a word to search for
// Return value: true if word is in the dictionary
bool Dictionary::has_word(std::string word) {
        int low = 0;
        int high = num_elements;//number of words in dic
        int mid;
        int c;
        while (low <= high) {
                c = high + low;
                mid = c / 2;
                if (wordlist[mid] == word) {
                        return true;
                } else if (wordlist[mid] > word) {
                        high = mid - 1;
                } else {
                        low = mid + 1;
                }
        }
        return false;
}
