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
    if (str == "chdir") return chdir;
    if (str == "ls") return ls;
    if (str == "copy") return string_code::copy;
    if (str == "ln") return ln;
    if (str == "lproot") return lproot;
    return other;
}
