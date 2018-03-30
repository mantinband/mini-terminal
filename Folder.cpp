//
// Created by amichai on 24/03/18.
//

#include <iomanip>
#include <sstream>
#include "Folder.h"

Folder::Folder(const string folderName):name(folderName) {}

Folder::~Folder() {
    for (vector<File*>::iterator i = files.begin(); i != files.end(); i++){
        (*i)->remove();
    }
    for (vector<Folder*>::iterator i = folders.begin(); i != folders.end(); i++){
        delete *i;
    }
}

bool Folder::fileExists(const string fileName) {
    for (vector<File*>::iterator i = files.begin(); i != files.end(); i++){
        if ((*i)->getName() == fileName){
            return true;
        }
    }
    return false;
}
bool Folder::folderExists(const string folderName) {
    for (vector<Folder*>::iterator i = folders.begin(); i != folders.end(); i++){
        if ((*i)->getName() == folderName){
            return true;
        }
    }
    return false;
}

const string &Folder::getName() const {
    return name;
}

vector<Folder*> &Folder::getFolders(){
    return folders;
}

vector<File*> &Folder::getFiles() {
    return files;
}

File* Folder::getFile(const string fileName) {
    for (vector<File*>::iterator i = files.begin(); i != files.end(); i++){
        if ((*i)->getName() == fileName){
            return *i;
        }
    }
    return NULL;
}

Folder *Folder::getFolder(string folderName) {
    for (vector<Folder*>::iterator i = folders.begin(); i != folders.end(); i++){
        if ((*i)->getName() == folderName){
            return *i;
        }
    }
    return NULL;
}

vector<Folder*>::iterator Folder::getFirstFolder(){
    return folders.begin();
}

vector<Folder*>::iterator Folder::getLastFolder(){
    return folders.end();
}

vector<File *>::iterator Folder::getFirstFile() {
    return files.begin();
}

vector<File *>::iterator Folder::getLastFile() {
    return files.end();
}

void Folder::deleteFolder(const string &toRemove) {
    for (vector<Folder*>::iterator i = folders.begin(); i != folders.end(); i++){
        if ((*i)->getName() == toRemove) {
            delete *i;
            folders.erase(i);
            return;
        }
    }
}

bool Folder::hasFolder(string toFind) {
    return getFolder(toFind) != NULL;
}

void Folder::deleteFile(string &toRemove) {
    for (vector<File*>::iterator i = files.begin(); i != files.end(); i++){
        if ((*i)->getName() == toRemove) {
            (*i)->remove();
            files.erase(i);
            return;
        }
    }
}

void Folder::printRec(string path, ostream &out) {
    stringstream s;
    s << path << "/" << name << ":";

    out << setw(15) << left << s.str();
    out << setw(15) << left << "|";
    out << setw(15) << left << "|" << endl;
    for (vector<File *>::iterator i = files.begin(); i != files.end(); i++){
        out << setw(15) << left << (*i)->getName();

        clearStringStream(s);
        s << "|" << *(*i)->getNumberOfReferences();
        out << setw(15) << left << s.str();

        clearStringStream(s);
        s << "|" << (*i)->getTimeSignature();
        out << setw(15) << left << s.str();
    }

    for (vector<Folder *>::iterator i = folders.begin(); i != folders.end(); i++){
        (*i)->printRec(path+"/"+name,out);
    }
}

void Folder::clearStringStream(stringstream &s) {
    s.clear();
    s.str(string());
}

