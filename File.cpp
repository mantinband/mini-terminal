//
// Created by amichai on 24/03/18.
//

#include <cstring>
#include "File.h"

const string &File::getName() const {
    return name;
}

void File::touch() {
}

File::File(string fileName)
: name(fileName) {
    try {
        ofs.open(fileName.c_str());
        ifs.open(fileName.c_str());
        if (!ofs.is_open() || !ifs.is_open()){
            throw failedToOpenFile();
        }
    } catch (string exceptionStatement){
        throw exceptionStatement;
    }
}


void File::operator[](pair<size_t, char> *posAndVal) {
    try {
        ofs.seekp(posAndVal->first);
        if (!ofs.good()) {
            throw filedToWriteToFile();
        }
        ofs << posAndVal->second;
        ofs.seekp(0);
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
}


const char File::operator[](size_t index) {
    char c = -128;

    try {
        ifs.seekg(index);
        if (!ifs.good()) {
            throw failedToReadFromFile();
        }
        ifs.get(c);
        ifs.seekg(0);
        return c;
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
    return c;
}

string File::failedToOpenFile(){
    return "ERROR: failed to open file";
}

string File::failedToReadFromFile(){
    return "ERROR: failed to read from file";
}

string File::filedToWriteToFile(){
    return "ERROR: filed to write to file";
}

ostream &File::cat(ostream &out) {
    if (ifs.is_open()) {
        out << ifs.rdbuf() << endl;
    }
    return out;
}
