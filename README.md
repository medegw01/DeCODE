# DeCODE
 NAME:    Michael Edegware
 DATE:    04.17.2016
 CLASS:   COMP 11
 PROJECT: 2
 
 ### KeyList Class
 
 This class is reads in input from the user and develops a linked list for
 encrypting or descrypting a text. It has the following public functions:
 
         KeyList()                      : the default constructor
         KeyList(std::string keyFile)   : the overload constructor
         ~KeyList()                     : the default destructor
         insert(std::string k)          : to insert a string into the list
                                          at the beginning of the list
         read_file(std::string keyFile) : to read a file of keywords (one word per line        
                                          into the keylist
         KeyWithResult next()           : to return the next KeyWithResult data in the list
                                          After each call to next(), the iterator variable 
                                          should point to the next node, and NULL if the end
                                          of the list has been  reached.
         reset_iterator()                :it resets the iterator to the head of the list
                                          to go through the list again
         update_result(std::string k,
                   float percentage, s
                   td::string p_text)    :search through the list and update k's 
                                          word_percentage and plaintext
                                                   
 The following structures:
 
         KeyWithResult                   :Used to store the key for a decryption attempt
         Node                            :This is a node for the list          
                                                  
 The following private elements:
 
         Node *head                       :this is pointer for the head of the list
         Node *iterator                   :the iterator for the list, which points
                                           to the next Node to retrieve during
                                           iteration, and will point to the head
         bubblesort()                     :a function that sorts the linked list in 
                                           decending order based on the keyWithResult percentage
### Dictionary Class


         This class is a dynamic array that reads in a dictionary
         from a file, and has the following public functions:
                    Dictionary() : the default constructor
                   ~Dictionary() : the default destructor
                    bool has_word(std::string word) : returns true
                             if the word is in the dictionary.
        The class has the following private methods:
                    void expand() : to expand the dynamic array
                    void read_dict_from_file(std::string filename) : this
                             reads in the words from a dictionary into the
                             dynamic array
 
        The class has the following private variables:
                   std::string wordlist : this holds the dynamic
                                          array pointer
                   int num_elements : the number of elements in the array
                   int capacity : the number of elements the array can hold 
 
                                           
 ### Operating Instruction:  
          The program receives an input string inform of either a ciphertext or plaintext. The
          ciphertext should only include lowercase letters and underscores. The command line must
          be either "--encrypt key" or "--decrypt key" or "--keyfile".
 
 ### Technical details:
 - phase1.cpp
 - readme.txt
 - keylist.cpp
 - keylist.h
 - cipher.cpp
 - dictionary.cpp
 - dictionary.h  
 
 ### To compile (all on one line):
 clang++ -Wall -Wextra -g cipher.cpp keylist.cpp dictionary.cpp phase1.cpp -o phase1
                                      
               