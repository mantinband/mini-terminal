//
// Created by amichai on 25/03/18.
//

#include "mainFunctions.h"
string_code stringHash(const string &str){
    if (str == "touch") return touch;
    if (str == "pwd") return pwd;
    if (str == "write") return write;
    if (str == "read") return read;
    if (str == "cat") return cat;
    if (str == "mkdir") return mkdir;
    if (str == "rmdir") return rmdir;
    if (str == "chdir") return chdir;
    if (str == "ls") return ls;
    if (str == "copy") return copyFile;
    if (str == "ln") return ln;
    if (str == "lproot") return lproot;
    if (str == "remove") return rm;
    if (str == "move") return mv;
    if (str == "wc") return wordCount;
    if (str == "--help") return help;
    return other;
}

void printCommands(){
    cout <<"read FILENAME POSITION" << endl;
    cout << "write FILENAME POSITION CHARACTER" << endl;
    cout << "touch FILENAME"<< endl;
    cout << "copy SOURCE_FILENAME TARGET_FILENAME" << endl;
    cout <<"remove FILENAME"<< endl;
    cout <<"move SOURCE_FILENAME TARGET_FILENAME"<< endl;
    cout <<"cat FILENAME"<< endl;
    cout <<"wc FILENAME"<< endl;
    cout <<"ln TARGET_FILENAME LINK_NAME"<< endl;
    cout <<"mkdir FOLDERNAME"<< endl;
    cout <<"chdir FOLDERNAME"<< endl;
    cout <<"rmdir FOLDERNAME"<< endl;
    cout <<"ls FOLDERNAME"<< endl;
    cout <<"lproot"<< endl;
    cout <<"pwd"<< endl;
    cout <<"exit"<< endl;
}