#include <iostream>
#include "Terminal.h"
#include "mainFunctions.h"
using namespace std;


int main() {
    Terminal terminal(cout);
    string input;
    cout << "Type --help to view commands" << endl;
    cout << terminal.getCurFolderPath() << "$ ";
    cin >> input;
    while (input != "exit"){
        string path;
        string pathDestination;
        size_t pos;
        char val;

        switch (stringHash(input)){
            case help:
                printCommands(); break;
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
                terminal.rmdir(path); break;
            case chdir:
                cin >> path;
                terminal.chdir(path); break;
            case ls:
                cin >> path;
                terminal.ls(path); break;
            case copyFile:
                cin >> path >> pathDestination;
                terminal.copy(path,pathDestination); break;
            case ln:
                cin >> path >> pathDestination;
                terminal.ln(path,pathDestination); break;
            case lproot:
                terminal.lproot(); break;
            case rm:
                cin >> path;
                terminal.remove(path); break;
            case mv:
                cin >> path;
                cin >> pathDestination;
                terminal.move(path,pathDestination); break;
            case wordCount:
                cin >> path;
                terminal.wc(path); break;
            default:
                cerr << "ERROR: invalid command. ";
                cout << "Type --help to view commands" << endl; break;
        }
        cout << terminal.getCurFolderPath() << "$ ";
        cin >> input;
    }

    return 0;
}


