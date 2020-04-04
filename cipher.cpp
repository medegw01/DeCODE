// cipher.cpp
// Purpose: A class for enciphering and deciphering
//          a transposition cipher
// By:      Chris Gregg
// Date:    20 March 2016
//
#include<iostream>
#include<cstdlib>
#include "cipher.h"

using namespace std;

// constructor
// Purpose: to set up the class
// Arguments: a string, "--encrypt" or "--decrypt" depending on 
//                      what we will accomplish
//            a string with the input text, either plaintext (encrypting)
//                      or ciphertext (decrypting)
//            a key made up of characters 
// Return value: none
Cipher::Cipher(string encrypt_or_decrypt, 
                             string key,
                             string inputtext)
{
        this->key = key;
        key_len = (int)key.length();
        order_columns();

        if (encrypt_or_decrypt == "encrypt"){
                will_encipher = true;
                plaintext = inputtext;
                plaintext = strip_and_underscore(plaintext);
                plaintext = pad(plaintext,key_len);
                parse_plaintext_to_cols();
        }
        else {
                will_encipher = false;
                ciphertext = inputtext;
                ciphertext = pad(ciphertext,key_len);
                parse_ciphertext_to_cols();
        }
        transform();
}


// Purpose: to destroy the class
// Arguments: none
// Return value: none
Cipher::~Cipher()
{
        delete [] cols;
        delete [] column_order;
}
// set_key()
// Purpose: to set the key and key length
// Arguments: a string (can be empty) and a key length
// Return value: none
void Cipher::set_key(string k, int klen)
{
	key = k;
	key_len = klen;
        order_columns(); // order the columns
}

// set_encipher
// Purpose: to set whether we are enciphering or deciphering
// Arguments: none
// Return value: none
void Cipher::set_encipher(bool will_encipher)
{
	this->will_encipher = will_encipher;
}

// get_key_len
// Purpose: accessor for key_len
// Arguments: none
// Return value: the key length 
int Cipher::get_key_len()
{
	return key_len;
}

// get_key
// Purpose: accessor for key
// Arguments: none
// Return value: the key string 
string Cipher::get_key()
{
	return key;
}

// order_columns()
// Purpose: order the columns based on the key
//          This is done alphabetically, so
//          a key of "hello" would put  
//          1,0,2,3,4 into the column_order array
//          because e (column 1) is alphabetically first, h is second, etc.
// Arguments: none
// Return value: none
// Note: will order 0,1,2,...,key_len-1 if key is the empty string
void Cipher::order_columns()
{
	string temp_key = key;
	int low_col = 0;
	
	column_order = new int[key_len];

        if (temp_key == "") { // no key!
                for (int i=0;i<key_len;i++) {
                        column_order[i] = i; // default order
                }       
        }
        else {          
                for (int i=0;i<key_len;i++) {
                        int key_min = 127; // max
                        for (int j=0;j<key_len;j++){ // search for lowest column
                                if (temp_key[j] < key_min) {
                                        key_min = temp_key[j];
                                        low_col = j;
                                }
                        }
                        column_order[i] = low_col;
                        temp_key[low_col] = 127; // done with this col
                }
        }
}

// get_column_order()
// Purpose: accessor for the column_order array
// Arguments: none
// Return value: the column_order array pointer 
int *Cipher::get_column_order()
{
        return column_order;
}


// parse_plaintext_to_cols()
// Purpose: takes the plaintext and puts it into columns
//          based on the length of the key
// Arguments: none
// Return value: none
void Cipher::parse_plaintext_to_cols()
{
        int msg_len = (int)plaintext.length();
        cols = new string[key_len]; // key_len number of columns
        for (int i=0;i<msg_len;i++){
                cols[i % key_len] += plaintext[i];
        }
}

// parse_ciphertext_to_cols()
// Purpose: puts the ciphertext into columns based on the
//          length of the key
// Arguments: none
// Return value: none
void Cipher::parse_ciphertext_to_cols()
{
        int msg_len = (int)ciphertext.length();

        // the number of rows should be an integer value
        int num_rows = msg_len / key_len;

        cols = new string[key_len]; // the number of columns is the key length
        for (int i=0;i<msg_len;i++){
                cols[i / num_rows] += ciphertext[i];
        }
}

// strip_and_underscore() 
// Purpose: clean up plaintext to be alpha-only,
//          lowercase, and spaces turned into underscores
// Arguments: a string to clean 
// Return value: a cleaned up string
string Cipher::strip_and_underscore(string s)
{
        string newstr;
        int s_len = (int)s.length();
        for (int i=0;i<s_len;i++){
                if (s[i] == SPACE){
                        newstr += UNDERSCORE;
                }
                else if (isalpha(s[i])) {
                        newstr += tolower(s[i]);
                }
        }
        return newstr;
}

// remove_underscores()
// Purpose: replaces underscores with spaces
// Arguments: a string with underscores 
// Return value: a string with the replacements made
string Cipher::remove_underscores(string s)
{
        string newstr;
        int s_len = (int)s.length();
        for (int i=0;i<s_len;i++){
                if (s[i] == UNDERSCORE) {
                        newstr+=SPACE;
                }
                else {
                        newstr+=s[i];
                }
        }
        return newstr;
}

// pad
// Purpose: to return an underscore padded string that has a
//          length divisible by len
// Arguments: a string and a length
// Return value: a new string padded with underscores
string Cipher::pad(string s, int len){
        while (s.length() % len != 0) {
                s += UNDERSCORE;
        }
        return s;	
}

// transform()
// Purpose: call the encrypt or decrypt depending on our mission
// Arguments: none
// Return value: none
void Cipher::transform()
{
        if (will_encipher) {
                encrypt();
        }
        else {
                decrypt();
        }	
}

// encrypt()
// Purpose: simply re-order the plaintext columns into ciphertext
// Arguments: none
// Return value: none
void Cipher::encrypt()
{
        for (int i=0;i<key_len;i++){
                ciphertext += cols[column_order[i]];
        }
        // convert back to spaces
        plaintext = remove_underscores(plaintext);
}

// decrypt()
// Purpose: return ciphertext to plaintext based on the key column ordering
// Arguments: none
// Return value: none
void Cipher::decrypt()
{
        plaintext = "";

        int num_rows = (int)ciphertext.length() / key_len;
        for (int i=0;i<num_rows;i++){
                for (int j=0;j<key_len;j++) {
                        for (int k=0;k<key_len;k++) {
                                // we need to find the lowest column first
                                if (column_order[k]==j){
                                        plaintext += cols[k][i];
                                }
                        }
                }
        }
        // clean up the plaintext
        plaintext = remove_underscores(plaintext);
}

// print()
// Purpose: Prints out the results of our encryption / decryption
// Arguments: none
// Return value: none
void Cipher::print()
{
        cout << "Plaintext:  " << plaintext;
        cout << endl;
        cout << "Ciphertext: " << ciphertext << endl;
}

// get_plaintext()
// Purpose: Returns the plaintext
// Arguments: none
// Return value: the plaintext in string form
string Cipher::get_plaintext()
{
        return plaintext;
}


// get_ciphertext()
// Purpose: Returns the ciphertext
// Arguments: none
// Return value: the ciphertext in string form
string Cipher::get_ciphertext()
{
        return ciphertext;
}
