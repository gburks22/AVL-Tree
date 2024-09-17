#include <iostream>
#include <sstream>
#include "AVL.h"
using namespace std;

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

string verifyName(string& name) {
    for (int i = 0; i < (int)name.length(); i++) {
        if (!isalpha(name[i]))
            return " ";
    }
    return name;
}

string verifyUFID(string& ufid) {
    for (char c : ufid) {
        if (!isdigit(c) || ufid.length() != 8)
            return " ";
    }
    return ufid;
}

int main(){
    AVLTree t;
    int commandCount = 0;
    int numOfCommands;
    cin >> numOfCommands;

    while (commandCount != numOfCommands) {
        // Project 1 Breakdown, slide 26, used for lines 35-39
        string line;
        getline(cin, line);
        istringstream in(line);
        string command;
        in >> command;
        if (command == "insert") {
            string bypass;
            getline(in, bypass, '"');
            string name;
            getline(in, name, '"');
            name = verifyName(name);
            if (name == " ") {
                cout << "unsuccessful" << endl;
                commandCount++;
                continue;
            }
            string bypass2;
            getline(in, bypass2, ' ');
            string ufid;
            getline(in, ufid, '\n');
            ufid = verifyUFID(ufid);
            if (ufid == " ") {
                cout << "unsuccessful" << endl;
                commandCount++;
                continue;
            }
            cout << "successful" << endl;
            t.insert(name, ufid);
            commandCount++;
            continue;
        }
        else if (command == "printInorder") {
            t.printInorder();
            commandCount++;
            continue;
        }
        else if (command == "printPreorder") {
            t.printPreorder();
            commandCount++;
            continue;
        }
        else if (command == "printPostorder") {
            t.printPostorder();
            commandCount++;
            continue;
        }
        else if (command == "printLevelCount") {
            t.printLevelCount();
            commandCount++;
            continue;
        }
        else if (command == "search") {
            string bypassSpace;
            getline (in, bypassSpace, ' ');
            if (in.peek() == '\"') {
                string bypass;
                getline(in, bypass, '"');
                string name;
                getline(in, name, '"');
                t.searchName(name);
                commandCount++;
                continue;
            } else {
                string ufid;
                in >> ufid;
                t.searchID(ufid);
                commandCount++;
                continue;
            }
        }
        else if (command == "remove") {
            string ufid;
            in >> ufid;
            if (isdigit(ufid.front())) {
                t.removeID(ufid);
                commandCount++;
                continue;
            }
        }
        else if (command == "removeInorder"){
            string stringN;
            in >> stringN;
            int n = stoi(stringN);
            t.removeInorder(n);
            commandCount++;
            continue;
        }

    }
    return 0;
}