#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include "hashtable.h"

using namespace std;

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

HashTable::HashTable(int len) {
    array.resize(len);
    nums.resize(len);

    for(int i = 0; i < len; i++) {
        array[i] = "EMPTY";
        nums[i] = 0;
    }
}

uint64_t HashTable::hash(string key) {
    uint64_t index = djb2(key);
    return index;
}

bool HashTable::hashInsert(Person* item, int size) {
    int i{};
    int bucketsProbed{};
    string info = setKey(item, key);
    int bucket = hash(info) % size;

    while(bucketsProbed < size) {
        if(array[bucket].compare(info) == 0) {
            nums[bucket]++;
            return true;
        }

        if(array[bucket].compare("EMPTY") == 0) {
            array[bucket] = info;
            return true;
        }

        i++;
        bucket = (hash(info) + (i * i) + i) % size;

        bucketsProbed++;
    }
    return false;
}

Person* createPerson() {
    Person *n = new Person;

    return n;
}

void printPerson(Person* p) {
    cout << p->id << ",";
    cout << p->first << ",";
    cout << p->last << ",";
    cout << p->email << ",";
    cout << p->phone << ",";
    cout << p->city << ",";
    cout << p->state << ",";
    cout << p->postalCode << endl;
}

void insertData(int counter, Person* person, string token) {
    if(counter == 0) {
        person->id = token;
    }

    else if(counter == 1) {
        person->first = token;
    }

    else if(counter == 2) {
        person->last = token;
    }

    else if(counter == 3) {
        person->email = token;
    }

    else if(counter == 4) {
        person->phone = token;
    }

    else if(counter == 5) {
        person->city = token;
    }

    else if(counter == 6) {
        person->state = token;
    }

    else if(counter == 7) {
        person->postalCode = token;
    }
}

string setKey(Person* p, string key) {
    if(key.compare("Id") == 0) {
        return p->id;
    } 

    else if(key.compare("FirstName") == 0) {
        return p->first;
    } 

    else if(key.compare("LastName") == 0) {
        return p->last;
    } 

    else if(key.compare("Email") == 0) {
        return p->email;
    } 

    else if(key.compare("Phone") == 0) {
        return p->phone;
    } 

    else if(key.compare("City") == 0) {
        return p->city;
    } 

    else if(key.compare("State") == 0) {
        return p->state;
    } 

    else if(key.compare("PostalCode") == 0) {
        return p->postalCode;
    } 

    return p->first;
}

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

Node::Node(Person* person) {
    this->p = person;
    this->next = nullptr;
}

List::List() {
    this->head = nullptr;
}

void List::insert(Person* p) {
    Node* person = new Node(p);
    
    if(head == nullptr) {
        head = person;
        return;
    }

    else {
        Node* n = head;
        while(1) {
            if(n->next == nullptr) {
                break;
            }
            n = n->next;
        }

        n->next = person;

        return;
    }
}

void List::printList() {
    Node* n = head;

    while(1) {
        if(n == nullptr) {
            break;
        }
        printPerson(n->p);
        n = n->next;
    }
}

void List::search(string key, string input) {
    Node* n = head;
    bool flag = 0;

    while(1) {
        if(n == nullptr) {
            if(flag == 0) {
                cout << "No results" << endl;
            }
            
            break;
        }

        string info = setKey(n->p, key);

        if(input.compare(info) == 0) {
            if(flag == 0) {
                cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                flag = 1;
            }

            printPerson(n->p);
        }

        n = n->next;
    }
}