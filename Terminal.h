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
    void read(const string path, const int pos) const;
    void write(const string path, const int pos, const char val);
    void cat(const string path) const;
    void mkdir(string path);
    void chdir(const string path) const;
    ostream &getOutputStream() const;
    const string &getCurFolderPath() const;
    Folder *getRoot() const;
    void pwd() const;
    void ls(string path);
    void copy(const string pathSource, const string pathDestination);
    void rmdir(const string path);
    void lproot() const;
    void ln(const string pathSource, const string pathDestination);

private:
    ostream &outputStream;
    string curFolderPath;
    Folder* root;
    Folder* curFolder;
    bool parsedPathIsInFolders(Folder *f, string folderName);
    bool parsedPathIsInFiles(Folder *f,string parsedPath);

    void printFolder(Folder *f) const;

    Folder *getFolder(string folderPath);

    string noSuchFile();

    string noSuchFolder();

    bool folderNameIsCurrentFolder(string folderName);

    bool folderNameStartPathIsLegal(string folderName);
};


#endif //EX1_TERMINAL_H
