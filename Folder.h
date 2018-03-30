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
    Folder(const string folderName);                //c'tor
    virtual ~Folder();                              //d'tor
    Folder(const Folder& rhs);                      //copy c'tor
    Folder & operator=(const Folder& rhs);

    void deleteFolder(const string &toRemove);      //deletes specified sub folder
    void deleteFile(string &fileToDelete);          //deletes specified sub file
    void printRec(string path, ostream &out);       //prints files content, and subfiles as well.

    vector<Folder *> & getFolders();
    vector<File *> & getFiles();
    Folder *getFolder(string folderName);       //returns specified sub folder
    File* getFile(const string fileName);       //returns specified sub file

    vector<Folder*>::iterator getFirstFolder();
    vector<Folder*>::iterator getLastFolder();
    vector<File*>::iterator getFirstFile();
    vector<File*>::iterator getLastFile();

    const string &getName() const;
    bool fileExists(const string fileName);         //returns true if file exists in folder
    bool hasFolder(string toFind);                  //returns true if folder has specified sub folder

private:
    string name;
    vector<Folder*> folders;
    vector<File*> files;

    void clearStringStream(stringstream& s);
};


#endif //EX1_FOLDER_H
