//
//
// Created by amichai on 24/03/18.

#include <cstring>
#include <sstream>
#include <unistd.h>
#include "File.h"


File::File(string fileName,ifstream* ifs, ofstream* ofs, int *numberOfReferences)
        :name(fileName),ifs(ifs), ofs(ofs), numberOfReferences(numberOfReferences) {
    updateTime();
    *numberOfReferences = *numberOfReferences+1;
}

File::File(string fileName)
:name(fileName),ifs(new ifstream),ofs(new ofstream),numberOfReferences(new int[1]){
    *numberOfReferences = 1;
    updateTime();
    try {
        ofs->open(fileName.c_str());
        ifs->open(fileName.c_str());
        if (!ofs->is_open() || !ifs->is_open()){
            throw failedToOpenFile();
        }
    } catch (exception e){
        cerr << e.what() << endl;
    }
}

File::File(const File &rhs) {
    ifs = rhs.getIfs();
    ofs = rhs.getOfs();
    numberOfReferences = rhs.getNumberOfReferences();
    name = rhs.getName();
    updateTime();
}

File &File::operator=(const File &rhs) {
    ifs = rhs.getIfs();
    ofs = rhs.getOfs();
    numberOfReferences = rhs.getNumberOfReferences();
    name = rhs.getName();
    updateTime();

    return *this;
}

const string &File::getName() const {
    return name;
}

void File::touch() {
    updateTime();
}



void File::operator[](pair<size_t, char> *posAndVal) {
    try {
        ofs->seekp(posAndVal->first);
        if (!ofs->good()) {
            throw failedToWriteToFile();
        }
        *ofs << posAndVal->second;
        ofs->seekp(0);
    } catch (exception e){
        cerr << e.what() << endl;
    }
    updateTime();
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
    } catch (exception e){
        cerr << e.what() << endl;
    }
    return c;
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
    std::remove(name.c_str());
}

void File::remove() {
    if (*numberOfReferences == 1){
        delete this;
    } else {
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

void File::updateTime() {
    time_t curTime = time(0);
    timeSignature = new char [strlen(ctime(&curTime))];
    strcpy(timeSignature,ctime(&curTime));
}

string File::wc(){
    stringstream s;
    s << numberOfWords() << "\t" << numberOfLines() << "\t" << numberOfChars();

    return s.str();
}

int File::numberOfWords(){
    bool inSpace = true;
    char curChar;
    int wordCount = 0;

    ifs->seekg(0);

    curChar = static_cast<char>(ifs->peek());
    while (curChar != EOF){
        if (!isspace(curChar) && curChar != '\n' && curChar != '\t'){
            if (inSpace){
                wordCount++;
            }
            inSpace = false;
        } else {
            inSpace = true;
        }
        ifs->seekg(1,ios_base::cur);
        curChar = static_cast<char>(ifs->peek());
    }

    return wordCount;
}

int File::numberOfLines(){
    int lineCount = 0;
    char curChar;

    ifs->seekg(0);

    curChar = static_cast<char>(ifs->peek());
    while(curChar != EOF){
        if (curChar == '\n'){
            lineCount++;
        }
        ifs->seekg(1,ios_base::cur);
        curChar = static_cast<char>(ifs->peek());
    }
    return lineCount;
}

int File:: numberOfChars(){
    int charCount = 0;
    char curChar;

    ifs->seekg(0);

    curChar = static_cast<char>(ifs->peek());
    while (curChar != EOF){
        if (!isspace(curChar) && curChar != '\n' && curChar != '\t'){
            charCount++;
        }
        ifs->seekg(1,ios_base::cur);
        curChar = static_cast<char>(ifs->peek());
    }

    return charCount;
}
