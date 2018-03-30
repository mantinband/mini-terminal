//
// Created by amichai on 24/03/18.
//

#ifndef EX1_FOLDER_H
#define EX1_FOLDER_H
#include <iostream>
#include <vector>
#include "File.h"

using namespace std;


class Folder {
public:
    Folder(const string folderName);
    virtual ~Folder();

    Folder *getFolder(string folderName);

    void deleteFolder(const string &toRemove);

    bool hasFolder(string toFind);

    void deleteFile(string &fileToDelete);

    void printRec(string path, ostream &out);

public:
    vector<Folder*> &getFolders() ;
    vector<File*> &getFiles() ;
    vector<Folder*>::iterator getFirstFolder();
    vector<Folder*>::iterator getLastFolder();
    vector<File*>::iterator getFirstFile();
    vector<File*>::iterator getLastFile();

    const string &getName() const;
    bool fileExists(const string fileName);
    bool folderExists(const string folderName);
    File* getFile(const string fileName);
private:
    string name;
    vector<Folder*> folders;
    vector<File*> files;

    void removeRec();

    void clearStringStream(stringstream& s);
};


#endif //EX1_FOLDER_H
