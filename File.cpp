//
//
// Created by amichai on 24/03/18.

#include <cstring>
#include <sstream>
#include <unistd.h>
#include "File.h"


File::File(string fileName,ifstream* ifs, ofstream* ofs, int *numberOfReferences)
        :name(fileName),ifs(ifs), ofs(ofs), numberOfReferences(numberOfReferences) {
    time_t curTime = time(0);
    timeSignature = ctime(&curTime);
    *numberOfReferences = *numberOfReferences+1;
}

File::File(string fileName)
:name(fileName),ifs(new ifstream),ofs(new ofstream),numberOfReferences(new int[1]){
    *numberOfReferences = 1;
    time_t curTime = time(0);
    timeSignature = new char [strlen(ctime(&curTime))];
    strcpy(timeSignature,ctime(&curTime));
    try {
        ofs->open(fileName.c_str());
        ifs->open(fileName.c_str());
        if (!ofs->is_open() || !ifs->is_open()){
            throw failedToOpenFile();
        }
    } catch (string exceptionStatement){
        throw exceptionStatement;
    }
}

void File::setName(const string &name) {
    File::name = name;
}

const string &File::getName() const {
    return name;
}

void File::touch() {
    time_t curTime = time(0);
    timeSignature = ctime(&curTime);
}


void File::link(){
    numberOfReferences++;
}


void File::operator[](pair<size_t, char> *posAndVal) {
    try {
        ofs->seekp(posAndVal->first);
        if (!ofs->good()) {
            throw filedToWriteToFile();
        }
        *ofs << posAndVal->second;
        ofs->seekp(0);
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
}

const char File::operator[](size_t index) {
    char c = -128;

    try {
        ifs->seekg(index);
        if (!ifs->good()) {
            throw failedToReadFromFile();
        }
        ifs->get(c);
        ifs->seekg(0);
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
    char c;
    ifs->seekg(0);
    c = static_cast<char>(ifs->peek());

    while (c != EOF){
        out << c;
        ifs->seekg(1,ios_base::cur);
        c = static_cast<char>(ifs->peek());
    }
    out << endl;
    return out;
}

File *File::copy(string &newFilesName) {
    File *theCopy = new File(newFilesName);
    char c;
    ifs->seekg(0);
    c = static_cast<char>(ifs->peek());

    for (size_t i=0; c != EOF; i++,c = static_cast<char>(ifs->peek())){
        theCopy->operator[](new pair<size_t ,char>(i,c));
        ifs->seekg(1,ios_base::cur);
    }
    return theCopy;
}

File::~File() {
    if (ifs->is_open()){
        ifs->close();
    }
    cout << "actually removing" << endl;
    std::remove(name.c_str());
}

void File::remove() {
    if (*numberOfReferences == 1){
        delete this;
    } else {
        cout << "removed, but not really" << endl;
        *numberOfReferences = *numberOfReferences-1;
    }
}

ifstream *File::getIfs() const {
    return ifs;
}

ofstream *File::getOfs() const {
    return ofs;
}
int* File::getNumberOfReferences() const {
    return numberOfReferences;
}

char *File::getTimeSignature() const {
    return timeSignature;
}
