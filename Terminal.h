//
// Created by amichai on 24/03/18.
//

#ifndef EX1_TERMINAL_H
#define EX1_TERMINAL_H

#include <iostream>
#include "File.h"
#include "Folder.h"

using namespace std;

class Terminal {
public:
    Terminal(ostream& out);
    Terminal(const Terminal& rhs);
    Terminal& operator=(const Terminal& rhs);
    virtual ~Terminal();
    void touch(string path);
    void read(const string path, const int pos) ;
    void write(const string path, const size_t pos, const char val);
    void cat(const string path);
    void mkdir(string path);
    void chdir(string path);
    ostream &getOutputStream() const;
    string getCurFolderPath() const;
    Folder *getRoot() const;
    void pwd() const;
    void ls(string path);
    void copy(const string pathSource, const string pathDestination);
    void rmdir(string path);
    void lproot() const;
    void ln(const string pathSource, const string pathDestination);
    Folder *setStartingFolder(stringstream &path);
private:
    Folder* root;
    Folder* curFolder;
    ostream &outputStream;
    string curFolderPath;
    bool parsedPathIsInFolders(Folder *f, string folderName);
    bool parsedPathIsInFiles(Folder *f,string parsedPath);

    void printFolder(Folder *f) const;

    Folder *getFolder(string folderPath);

    string noSuchFile();
    string noSuchFolder();
    bool folderNameIsCurrentFolder(string folderName);
    bool folderNameStartPathIsLegal(string folderName);
    vector<string> * parsePath(string path);

    string folderAlreadyExists();


    Folder *getFolderXFromEnd(vector<string> *parsedPath, unsigned int posFromEnd);
};


#endif //EX1_TERMINAL_H
