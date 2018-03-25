#include <iostream>
#include "Terminal.h"
#include "mainFunctions.h"
using namespace std;


int main() {
    Terminal terminal(cout);
    string input;

    cin >> input;
    while (input != "exit"){
        string path;
        string pathDestination;
        int pos;
        char val;

        switch (stringHash(input)){
            case touch:
                cin >> path;
                terminal.touch(path); break;
            case pwd:
                terminal.pwd(); break;
            case write:
                cin >> path >> pos >> val;
                terminal.write(path,pos,val); break;
            case read:
                cin >> path >> pos;
                terminal.read(path,pos); break;
            case cat:
                cin >> path;
                terminal.cat(path); break;
            case mkdir:
                cin >> path;
                terminal.mkdir(path); break;
            case rmdir:
                cin >> path;
                terminal.rmdir(path);
            case chdir:
                cin >> path;
                terminal.chdir(path); break;
            case ls:
                terminal.ls(); break;
            case string_code::copy:
                cin >> path >> pathDestination;
                terminal.copy(path,pathDestination); break;
            case ln:
                cin >> path >> pathDestination;
                terminal.ln(path,pathDestination); break;
            case lproot:
                terminal.lproot(); break;

            default:
                cout << "ERROR: invalid command" << endl; break;
        }
        cin >> input;
    }

    return 0;
}


