//
// Created by amichai on 24/03/18.
//

#ifndef EX1_FILE_H
#define EX1_FILE_H
#include <iostream>
#include <fstream>

using namespace std;

class File {
public:
    File(string fileName);
    const string &getName() const;
    void touch();
    void operator[](pair<size_t, char> *posAndVal);
    const char operator[](size_t index);
    ostream & cat(ostream &out);
private:
    string timeSignature;
    string name;
    ifstream ifs;
    ofstream ofs;
    string failedToOpenFile();
    string failedToReadFromFile();
    string filedToWriteToFile();
};


#endif //EX1_FILE_H
