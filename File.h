//
// Created by amichai on 24/03/18.
//

#ifndef EX1_FILE_H
#define EX1_FILE_H
#include <iostream>
using namespace std;

class File {
public:
    File(string fileName);
    const string &getName() const;
    void touch();
private:
    string name;

};


#endif //EX1_FILE_H
