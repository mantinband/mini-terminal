//
// Created by amichai on 24/03/18.
//

#include <sstream>
#include "Terminal.h"

Terminal::Terminal(ostream &output)
:root(new Folder("V")),curFolder(root) ,outputStream(output),curFolderPath("V/"){
}

Terminal::Terminal(const Terminal &rhs)
:root(rhs.getRoot()),curFolder(root),outputStream(rhs.getOutputStream()),curFolderPath(rhs.getCurFolderPath()) {}
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
    try {
        vector<string> *parsedPath = parsePath(path);
        Folder *f;

        if (parsedPath->at(0) == root->getName()) {
            f = root;
        } else if (parsedPath->at(0) == curFolder->getName()) {
            f = curFolder;
        } else if (parsedPath->size() == 1) {
            curFolder->getFolders().push_back(new Folder(parsedPath->at(0)));
            return;
        } else {
            throw noSuchFolder();
        }

        if (parsedPath->size() > 2) {
            vector<string>::iterator currentFolderIterator = parsedPath->begin();
            currentFolderIterator++;
            for (unsigned int i = 0; i < parsedPath->size() - 2; i++) {
                if (f->hasFolder(*currentFolderIterator)) {
                    f = f->getFolder(*currentFolderIterator);
                    currentFolderIterator++;
                } else {
                    throw noSuchFolder();
                }
            }
        }
        f->getFolders().push_back(new Folder(parsedPath->at(parsedPath->size() - 1)));
        return;
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
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

void Terminal::chdir(string path) {
    {
        vector<string> *parsedPath = parsePath(path);

        if (parsedPath->at(0) == root->getName()){
            Folder *f= root;
            if (parsedPath->size() > 1){
                vector<string>::iterator currentFolderIterator = parsedPath->begin();

                for (int i=0; i<parsedPath->size()-1; i++){
                    if (f->hasFolder(*currentFolderIterator)){
                        f = f->getFolder(*currentFolderIterator);
                    } else {
                        throw noSuchFolder();
                    }
                }
            }
            curFolder = f;
            curFolderPath = path;
        } else if (parsedPath->at(0) == curFolder->getName()){
            
        } else {
            throw noSuchFolder();
        }

    }

    if (path[path.length()-1] != '/'){
        path += '/';
    }

    if (path == root->getName() + "/"){
        curFolder = root;
        curFolderPath = path;
    } else {
        try {
            curFolder = getFolder(path);
            if (path[0] == root->getName()[0]){
                curFolderPath = path;
            } else {
                curFolderPath = curFolderPath + path;
            }
            cout << "cur folder is " + curFolder->getName() << endl;
        } catch (string exceptionStatement) {
            cerr << exceptionStatement << endl;
        }
    }
}

void Terminal::pwd() const {
    outputStream << curFolderPath << endl;
}

void Terminal::ls(string path) {
    if (path[path.length()-1] != '/'){
        path+='/';
    }
    if (path == root->getName() + "/"){
        cout << path + ":" << endl;
        printFolder(root);
    } else if (path == curFolder->getName()+"/"){
        cout << path + ":" << endl;
        printFolder(curFolder);
    } else {
        try {
            Folder *f = getFolder(path);
            cout << path + ":" << endl;
            printFolder(f);
        } catch (string exceptionStatement) {
            cerr << exceptionStatement << endl;
        }
    }
}

void Terminal::rmdir(string path) {
    vector<string> *parsedPath = parsePath(path);
    string toRemove = parsedPath->at(parsedPath->size()-1);
    Folder *toRemoveFatherFolder;

    if (parsedPath->at(0) == root->getName()){
        toRemoveFatherFolder = root;
    } else {
        toRemoveFatherFolder = curFolder;
    }

    vector<string>::iterator curFolderIterator = parsedPath->begin();

    if (parsedPath->size() > 2){
        curFolderIterator++;
        for (unsigned int i=0; i < parsedPath->size()-2 ; i++, curFolderIterator++){
            if (toRemoveFatherFolder->folderExists(*curFolderIterator)){
                toRemoveFatherFolder = toRemoveFatherFolder->getFolder(*curFolderIterator);
            } else {
                throw noSuchFolder();
            }
        }
    }
    if (toRemoveFatherFolder->folderExists(toRemove)){
        toRemoveFatherFolder->deleteFolder(toRemove);
    } else {
        throw noSuchFolder();
    }
}

void Terminal::lproot() const {

}

void Terminal::touch( string path) {
    try {
        Folder *f;
        vector<string> *parsedPath = parsePath(path);

        if (parsedPath->at(0) == root->getName()) {
            f = root;
        } else if (parsedPath->at(0) == curFolder->getName()) {
            f = curFolder;
        } else if (parsedPath->size() == 1) {
            curFolder->getFiles().push_back(new File(parsedPath->at(0)));
            return;
        } else {
            throw noSuchFolder();
        }

        if (parsedPath->size() > 2){
            vector<string>::iterator currentFolderIterator = parsedPath->begin();
            currentFolderIterator++;
            for (unsigned int i=0; i<parsedPath->size()-2; i++) {
                if (f->hasFolder(*currentFolderIterator)){
                    f = f->getFolder(*currentFolderIterator);
                    currentFolderIterator++;
                } else {
                    throw noSuchFolder();
                }
            }
        }
        f->getFiles().push_back(new File(parsedPath->at(parsedPath->size()-1)));
    } catch (string exeptionStatement){
        cerr << exeptionStatement << endl;
    }
}

void Terminal::ln(const string pathSource, const string pathDestination) {

}

void Terminal::copy(const string pathSource, const string pathDestination) {

}

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
    vector<string> *parsedPath = parsePath(folderPath);
    Folder *f;

    if (parsedPath->at(0) == root->getName()){
        f = root;
    } else if (parsedPath->at(0) == curFolder->getName()){
        f = curFolder;
    } else {
        throw noSuchFolder();
    }


    vector<string>::iterator i = parsedPath->begin();
    i++;

    while (i != parsedPath->end()){
        if (parsedPathIsInFolders(f,*i)){
            f = f->getFolder(*i);
        } else {
            throw noSuchFolder();
        }
        i++;
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

Folder *Terminal::setStartingFolder(stringstream &s) {
    Folder *f;
    string folderName;

    getline(s, folderName, '/');
    if (folderNameStartPathIsLegal(folderName)) {
        if (folderName == root->getName()){
            f = root;
        } else {
            f = curFolder;
        }
    } else {
        throw noSuchFolder();
    }

    return f;
}

vector<string> *Terminal::parsePath(string path) {
    stringstream s(path);
    string folderName;
    vector<string> *parsedPath = new vector<string>();

    if (path[path.length()-1] != '/'){
        path += "/";
    }
    do {
        getline(s, folderName, '/');
        if (!folderName.empty())
        parsedPath->push_back(folderName);
    } while (!s.eof());

    return parsedPath;
}

string Terminal::concatinatePath(vector<string> *parsedPath, int numberOfFolders) {
    string concatinatedPath = "";
    vector<string>::iterator it = parsedPath->begin();

    for (int i=0 ; i < numberOfFolders ; i++){
        concatinatedPath += *it;
        concatinatedPath += "/";
        it++;
    }
    return concatinatedPath;
}
