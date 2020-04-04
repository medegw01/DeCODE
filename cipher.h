#ifndef CIPHER_H
#define CIPHER_H

#include<string>

const char SPACE = ' ';
const char UNDERSCORE = '_';

class Cipher {
        public:
                Cipher(std::string encrypt_or_decrypt,
                                std::string key,
                                std::string inputtext);
                ~Cipher(); // destructor
                std::string get_plaintext();
                std::string get_ciphertext();
                std::string get_key();

                void print();
        private:
                std::string plaintext;
                std::string ciphertext;
                std::string key;

                void set_key(std::string k,int klen);
                void set_encipher(bool will_encipher);
                int *get_column_order();
                int get_key_len();
                void transform();
                void order_columns();
                int key_len;
                int *column_order;
                bool will_encipher;
                void parse_plaintext_to_cols();
                void parse_ciphertext_to_cols();
                std::string pad(std::string s,int len);
                std::string strip_and_underscore(std::string s);
                std::string remove_underscores(std::string s);

                void encrypt();
                void decrypt();

                std::string *cols;
};
#endif

