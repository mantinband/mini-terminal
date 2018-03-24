//
// Created by amichai on 24/03/18.
//

#include "Folder.h"

Folder::Folder(const string folderName):name(folderName) {}

Folder::~Folder() {
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
    for (vector<File*>::iterator i = files.begin(); i != files.end(); i++){
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

