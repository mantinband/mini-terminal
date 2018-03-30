//
// Created by amichai on 24/03/18.
//

#ifndef EX1_FILE_H
#define EX1_FILE_H
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class File {
public:
    File(string fileName);
    File(string fileName,ifstream *ifs, ofstream *ofs, int *numberOfReferences);
    virtual ~File();

    void operator[](pair<size_t, char> *posAndVal);

    char *getTimeSignature() const;

    const char operator[](size_t index);

    void touch();
    ostream &cat(ostream &out);
    File *copy(string &basicString);
    void remove();

    const string &getName() const;
    void setName(const string &name);
    int * getNumberOfReferences() const;
    ifstream *getIfs() const;
    ofstream *getOfs() const;
    void link();

private:
    string name;
    ifstream *ifs;
    ofstream *ofs;
    int *numberOfReferences;
    char *timeSignature;
    string failedToOpenFile();
    string failedToReadFromFile();
    string filedToWriteToFile();

    void updateTime();
};


#endif //EX1_FILE_H
