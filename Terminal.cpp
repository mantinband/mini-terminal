//
// Created by amichai on 24/03/18.
//

#include <sstream>
#include "Terminal.h"

Terminal::Terminal(ostream &output)
:outputStream(output), root(new Folder("V")),curFolderPath("V/"),curFolder(root) {
}

Terminal::~Terminal() {
    delete(root);
}

void Terminal::read(const string path, const int pos) const {

}

void Terminal::write(const string path, const int pos, const char val) {

}

void Terminal::cat(const string path) const {

}

void Terminal::mkdir(string path) {
    stringstream s(path);
    string folderName;
    Folder *f;

    if (path[path.length()-1] != '/'){
        path += '/';
    }

    getline(s,folderName,'/');

    try {
        if (folderNameStartPathIsLegal(folderName)) {
            if (folderName == root->getName()) {
                f = root;
            } else {
                f = curFolder;
            }
        } else {
            throw noSuchFolder();
        }
        getline(s,folderName,'/');
        while (!s.eof()) {
            if (parsedPathIsInFolders(f, folderName)) {
                f = f->getFolder(folderName);
            } else {
                noSuchFolder();
            }
            getline(s, folderName, '/');
        }
        f->getFolders().push_back(new Folder(folderName));
    } catch (string execptionStatement){
        cerr << execptionStatement << endl;
    }
}

void Terminal::chdir(const string path) const {

}

void Terminal::pwd() const {
    outputStream << curFolderPath << endl;
}

void Terminal::ls(string path) {
    if (path[path.length()-1] != '/'){
        path += '/';
    }
    try {
        Folder *f = getFolder(path);
        cout << path + ":" << endl;
        printFolder(f);
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
}

void Terminal::rmdir(const string path) {

}

void Terminal::lproot() const {

}

void Terminal::touch( string path) {
    stringstream s(path);
    string parsedPath;
    Folder *f;

    if (path[path.length()-1] != '/'){
        path += '/';
    }

    try {
        getline(s, parsedPath, '/');
        if (folderNameStartPathIsLegal(parsedPath)) {
            if (parsedPath == root->getName()){
                f = root;
            } else {
                f = curFolder;
            }
        } else {
            throw noSuchFolder();
        }
        getline(s, parsedPath, '/');
        while (!s.eof()) {
            if (parsedPathIsInFolders(f, parsedPath)) {
                f = f->getFolder(parsedPath);
                cout << "cur folder is " + f->getName() << endl;
            } else if (parsedPathIsInFiles(f,parsedPath)) {
                f->getFile(parsedPath)->touch();
                return;
            } else {
                string restOfPath;
                getline(s,restOfPath,'\n');
                f->getFiles().push_back(new File(parsedPath+"/"+restOfPath));
                outputStream << "added " + parsedPath << endl;
                return;
            }
            getline(s, parsedPath, '/');
        }

        f->getFiles().push_back(new File(parsedPath));
        outputStream << "added " + parsedPath << endl;
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
}

void Terminal::ln(const string pathSource, const string pathDestination) {

}

void Terminal::copy(const string pathSource, const string pathDestination) {

}

Terminal::Terminal(const Terminal &rhs)
:outputStream(rhs.getOutputStream()),curFolderPath(rhs.getCurFolderPath()),root(rhs.getRoot()) {}

ostream &Terminal::getOutputStream() const {
    return outputStream;
}

const string &Terminal::getCurFolderPath() const {
    return curFolderPath;
}

Folder *Terminal::getRoot() const {
    return root;
}

Terminal &Terminal::operator=(const Terminal &rhs) {
    *this = rhs;
    return const_cast<Terminal &>(rhs);
}

bool Terminal::parsedPathIsInFiles(Folder *f, string parsedPath) {
    return f->fileExists(parsedPath);
}

bool Terminal::parsedPathIsInFolders(Folder *f, string folderName) {
    return f->folderExists(folderName);
}

void Terminal::printFolder(Folder *f) const {
    for (vector<Folder*>::iterator i = f->getFirstFolder(); i != f->getLastFolder(); i++){
        outputStream << (*i)->getName() + "/" << endl;
    }

    for (vector<File*>::iterator i = f->getFirstFile(); i != f->getLastFile(); i++){
        outputStream << (*i)->getName() << endl;
    }
}

Folder *Terminal::getFolder(string folderPath) {
    stringstream s(folderPath);
    string folderName;
    Folder *f;

    if (folderName[folderName.length()-1] != '/'){
        folderName += '/';
    }

    getline(s,folderName,'/');
    if (!folderNameStartPathIsLegal(folderName)){
        throw noSuchFolder();
    } else {
        if (folderName == root->getName()){
            f = root;
        } else {
            f = curFolder;
        }
    }

    getline(s,folderName,'/');
    while (!s.eof()){
        if (parsedPathIsInFolders(f, folderName)){
            f = f->getFolder(folderName);
        } else {
            throw noSuchFolder();
        }
        getline(s,folderName,'/');
    }
    return f;
}

string Terminal::noSuchFile() {
    return "ERROR: no such file name";
}

string Terminal::noSuchFolder() {
    return "ERROR: no such folder";
}

bool Terminal::folderNameIsCurrentFolder(string folderName) {
    if (curFolder->getName()+"/" == folderName || root->getName() + "/" == folderName){
        return true;
    }
    return false;
}

bool Terminal::folderNameStartPathIsLegal(string folderName) {
    if (folderName == root->getName() || folderName == curFolder->getName()) {
        return true;
    }
    return false;
}

