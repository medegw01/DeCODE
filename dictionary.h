/*******************************************************************************
 * KeyList Class Interface                                                     *
 * For DeCode (COMP 11 Project 2 | 2016 Spring)                           *
 * written by: Michael Edegware                                                *
 * Date: 4/18/2016                                                             *
 * Joke: Q. A programmer was going for work, so his wife told him that while he
 *       is out, he should get some decorations for her. He never came back.   *
 ******************************************************************************/
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>

const int CAPACITY = 10;
const std::string BLANK = "";

static std::string DICT_FILE = "words.txt";

class Dictionary {
      public:
        // constructor calls read_dict_from_file()
        // with the filename
        Dictionary();  // constructor
        ~Dictionary(); // desctructor

        // has_word()
        // Purpose: search for the word in the dictionary
        // Argument: a word to search for
        // Return value: true if word is in the dictionary
        bool has_word(std::string word);

      private:
        // the word list
        std::string *wordlist;

        // word list variables
        int num_elements;
        int capacity;

        // expand function for dynamic array
        void expand();

        // reads in the dictionary from a file
        void read_dict_from_file(std::string filename);
};
#endif
