#include <iostream>
#include "Terminal.h"

using namespace std;

enum string_code{
    touch,
    pwd,
    write,
    read,
    cat,
    mkdir,
    rmdir,
    chdir,
    ls,
    copy,
    ln,
    lproot,
    other
};
string_code stringHash(const string &str);

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


string_code stringHash(const string &str){
    if (str == "touch") return touch;
    if (str == "pwd") return pwd;
    if (str == "write") return write;
    if (str == "read") return read;
    if (str == "cat") return cat;
    if (str == "mkdir") return mkdir;
    if (str == "chdir") return chdir;
    if (str == "ls") return ls;
    if (str == "copy") return string_code::copy;
    if (str == "ln") return ln;
    if (str == "lproot") return lproot;
    return other;
}
