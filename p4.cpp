#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "hashtable.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    HashTable table(tableSize);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    int numPeople{};
    table.key = key;
    List peopleList;
   
    string line, token;
    getline(file, line);
    while (getline(file, line)) {
        int counter{};
        Person* n = createPerson();
        istringstream iss(line);

        while (getline(iss, token, '\t')) {
            insertData(counter, n, token);
            counter++;
        }
        
        peopleList.insert(n);

        table.hashInsert(n, tableSize);

        numPeople++;
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            for(int i = 0; i < tableSize; i++) {
                if(table.array[i].compare("EMPTY") != 0) {
                    cout << i << ": " << table.array[i] << " (" << table.nums[i] + 1 << ")," << endl;
                }
            }
        }

        else if (cmd == "lookup") {
            getVal(cin, val);
            peopleList.search(key, val);
        }

        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
