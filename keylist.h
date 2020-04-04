/*******************************************************************************
 * KeyList Class Interface                                                     *
 * For Pacman Game (COMP 11 Project 2 | 2016 Spring)                           *
 * written by: Michael Edegware                                                *
 * Date: 4/18/2016                                                             *
 * Joke: Q. A programmer was going for work, so his wife told him that while he
 *       is out, he should get some decorations for her. He never came back.   *
 ******************************************************************************/
#ifndef KEYLIST_H
#define KEYLIST_H

#include <string>

// KeyWithResult Struct
// Used to store the key for a decryption attempt
struct KeyWithResult {
        std::string key;       // the key for the attempt
        float word_percentage; // the percentage of words that are in english
        std::string plaintext; // the resulting string after decryption
};

// Node for the list
// The data is a KeyWithResult struct
// The next is a pointer to the next Node
struct Node {
        KeyWithResult kwr;
        Node *next;
};

// KeyList Class definition
// A KeyList is a linked list with a head and an "iterator" that
// walks through a list one node at a time.
class KeyList {
      public:
        KeyList();                    // default constructor
        KeyList(std::string keyFile); // constructor with filename
        ~KeyList();                   // destructor

        // read_file()
        // Purpose: to read a file of keywords (one word per line)
        //          into the keylist
        void read_file(std::string keyFile);

        // insert()
        // Purpose: to insert a string into the list
        //          at the beginning of the list
        // Note: insert should call reset_iterator()
        void insert(std::string k);

        // next()
        // Purpose: to return the next KeyWithResult data in the list
        //          After each call to next(), the
        //          iterator variable should point
        //          to the next node, and NULL if the end of the list
        //          has been reached.
        // Return value: the KeyWithResult data pointed
        //               to by the iterator pointer. If
        //               at the end of the list, the
        //               word_percentage for the
        //               data should be "-1.0"
        KeyWithResult next();

        // reset_iterator()
        // Purpose: reset the iterator to the head
        //          of the list to go through the list again
        void reset_iterator();

        // update_result()
        // Purpose: search through the list and
        //          update k's word_percentage and
        //          plaintext
        // Arguments: the key to search for in the
        //            list, and the percentage value
        void update_result(std::string k, float percentage, std::string p_text);

      private:
        // the head of the list
        Node *head;

        // the iterator for the list, which points
        // to the next Node to retrieve during
        // iteration, and will point to the head
        // after an insert() or after reset_iterator()
        Node *iterator;
        // a function that sort the list in ascending order;
        void bubblesort();
};

#endif
