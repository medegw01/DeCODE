/*******************************************************************************
 * KeyList Class Implementation                                                *
 * For Pacman Game (COMP 11 Project 2 | 2016 Spring)                           *
 * written by: Michael Edegware                                                *
 * Date: 4/18/2016                                                             *
 * Joke: Q. How can a man go eight days without sleep?                         *
 * A. He sleeps at night                                                       *
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include "keylist.h"

using namespace std;
/*
 * KeyList constructor
 * Purpose: to initialize private members
 * Arguments: none (constructor)
 * Return value: none (constructor)
*/
KeyList::KeyList() {
        head = NULL;
        iterator = head;
}
/*
 * KeyList constructor(over loaded)
 * Purpose: to initialize private members
 * Arguments: string
 * Return value: none (constructor)
*/
KeyList::KeyList(std::string keyFile) {
        head = NULL;
        iterator = head;
        read_file(keyFile);
}
/*
 * KeyList destructor(over loaded)
 * Purpose: to initialize private members
 * Arguments: none(destructor)
 * Return value: none (destructor)
*/
KeyList::~KeyList() {
        Node *current = head; // a pointer to store the head
        // before deleting
        while (current != NULL) {
                Node *temp = current->next;
                delete current;
                current = temp;
        }
}
/*read_file()
 * purpose: to read a file of keywords (one word per line) into the keylist
 * Argument: string
 * Return: none
  */
void KeyList::read_file(string keyFile) {
        string line;
        ifstream inputFile(keyFile.c_str());
        if (inputFile.is_open()) {
                while (getline(inputFile, line)) {
                        insert(line);
                }
                inputFile.close();
        }
}
/* insert()
 * purpose: to insert a string into the list
 *          at the beginning of the list
 * Argument: string
 * Return: none
  */
void KeyList::insert(std::string k) {
        Node *temp = new Node;
        temp->kwr.word_percentage = 0;
        temp->kwr.key = k;
        temp->next = head;
        head = temp;
        reset_iterator(); // to reset iterator to the head
}
/* insert()
 * purpose: to return the next KeyWithResult data in the list
 *          After each call to next(), the iterator variable should point
 *          to the next node, and NULL if the end of the list has been reached.
 * Argument: string
 * Return: the KeyWithResult data pointed to by the iterator pointer. If
 *           at the end of the list, the word_percentage for the
 *           data should be "-1.0"
 */
KeyWithResult KeyList::next() {
        Node *temp = iterator;
        KeyWithResult at_end;
        if (iterator->next == NULL) { // at end of the list
                at_end = temp->kwr;
                at_end.word_percentage = -1;
                return at_end;
        }

        else {
                iterator = iterator->next; // not at the end
                return temp->kwr;
        }
}
/*reset_iterator()
 * purpose: reset the iterator to the head
 *           of the list to go through the list again
 * Argument: nond
 * Return: none
  */
void KeyList::reset_iterator() {
        iterator = head;
}
/*update_result()
 * purpose: search through the list and
 *        update k's word_percentage and  plaintext
 * Argument: two strings, and a float
 * Return: none
  */
void KeyList::update_result(std::string k, float percentage,
                            std::string p_text) {
        Node *current = head;
        while (current != NULL) {
                if (current->kwr.key == k) {
                        current->kwr.word_percentage = percentage;
                        current->kwr.plaintext = p_text;
                }
                current = current->next;
        }
        bubblesort();
}
/* bubblesort()
 * purpose: to sort the linked list in ascending order in terms
 *          of percentage.
 * Argument: none
 * Return: none
 */
void KeyList::bubblesort() { /*I got the idea for bubble sorting from
         https://www.youtube.com/watch?v=QcXLgNDIskE*/
        Node *current, *temp, *previous, *position;
        position = new Node;
        position->next = head;
        head = position;
        bool stop = false; // to stop when finish sorting
        while (!stop) {
                current = position->next;
                previous = position;
                temp = current->next;
                stop = true;
                while (temp != NULL) {
                        if (temp->kwr.word_percentage >
                            current->kwr.word_percentage) {
                                Node *temp2 = temp->next;
                                temp->next = previous->next;
                                previous->next = current->next;
                                current->next = temp2;
                                previous = temp;
                                temp = temp2;
                                stop = false;
                        } else {
                                temp = temp->next;
                                current = current->next;
                                previous = previous->next;
                        }
                }
        }
        head = head->next;//tranverse to next
}
