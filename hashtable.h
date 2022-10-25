#ifndef HASHTABLE_H

#define HASHTABLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

class Person {
public:
    std::string id;
    std::string first;
    std::string last;
    std::string email;
    std::string phone;
    std::string city;
    std::string state;
    std::string postalCode;
};

class HashTable {
    public:
    std::vector<std::string> array;
    std::vector<int> nums;
    std::string key;

    HashTable(int len); // default constructor
    uint64_t hash(string key); // returns index for insertion
    bool hashInsert(Person* item, int size); // inserts into array
};

class Node {
    public:
    Person* p;
    Node* next;

    Node(Person* person); // default constructor
};

class List {
    public:
    Node* head;

    List(); // default constructor 
    void insert(Person* p); // inserta at the back of the list
    void printList(); // prints the list
    void search(string key, string input); // searches for a specific string stored in the Persons stored in the list
};

uint64_t djb2(string str); // converts strings to uint64_t
bool isValidKey(const string &key); // checks validity of key
void getVal(istream &is, string &str); // returns the value
string setKey(Person* p, string key); // returns the key member of the Person
void insertData(int counter, Person* person, string token); // sets specific members of the inputed Person class
void printPerson(Person* p); // prints the inputed persons values
Person* createPerson(); // creates a new person on the heap

#endif