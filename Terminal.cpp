//
// Created by amichai on 24/03/18.
//

#include <sstream>
#include "Terminal.h"

Terminal::Terminal(ostream &output)
:root(new Folder("V")),curFolder(root) ,outputStream(output),curFolderPath("V"){
}

Terminal::Terminal(const Terminal &rhs)
:root(rhs.getRoot()),curFolder(root),outputStream(rhs.getOutputStream()),curFolderPath(rhs.getCurFolderPath()) {}
Terminal::~Terminal() {
    delete(root);
}

void Terminal::read(const string path, const int pos) {
    Folder *f;
    vector<string> *parsedPath = parsePath(path);

    try {
        f = getFolderXFromEnd(parsedPath,1);
        if (f->fileExists(parsedPath->at(parsedPath->size() - 1))) {
            outputStream << f->getFile(parsedPath->at(parsedPath->size() - 1))->operator[](pos) << endl;
        } else {
            throw noSuchFile();
        }
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
}

void Terminal::write(const string path, const size_t pos, const char val) {
    Folder *f;
    vector<string> *parsedPath = parsePath(path);

    if (parsedPath->size() == 1 && curFolder->fileExists(parsedPath->at(0))){
        curFolder->getFile(parsedPath->at(parsedPath->size() - 1))->operator[](new pair<size_t, char>(pos, val));
    } else {
        try {
            f = getFolderXFromEnd(parsedPath, 1);

            if (f->fileExists(parsedPath->at(parsedPath->size() - 1))) {
                f->getFile(parsedPath->at(parsedPath->size() - 1))->operator[](new pair<size_t, char>(pos, val));
            } else {
                throw noSuchFile();
            }
        } catch (string exceptionStatement) {
            cerr << exceptionStatement << endl;
        }
    }
}



void Terminal::cat(const string path) {
    vector<string> *parsedPath = parsePath(path);

    if (parsedPath->size() == 1 && curFolder->fileExists(parsedPath->at(0))) {
        curFolder->getFile(parsedPath->at(0))->cat(outputStream);
    } else {
        try {
            Folder *f = getFolderXFromEnd(parsedPath, 1);
            if (f->fileExists(parsedPath->at(parsedPath->size() - 1))) {
                f->getFile(parsedPath->at(parsedPath->size() - 1))->cat(outputStream);
            } else {
                throw noSuchFolder();
            }
        } catch (string exceptionStatement) {
            cerr << exceptionStatement << endl;
        }
    }
}
void Terminal::mkdir(string path) {
    try {
        vector<string> *parsedPath = parsePath(path);
        Folder *f;

        if (parsedPath->size() == 1){
            if (curFolder->hasFolder(parsedPath->at(0))){
                throw folderAlreadyExists();
            }
            curFolder->getFolders().push_back(new Folder(parsedPath->at(0)));
            return;
        }
        f = getFolderXFromEnd(parsedPath,1);
        if (f->hasFolder(parsedPath->at(parsedPath->size()-1))){
            throw folderAlreadyExists();
        }
        f->getFolders().push_back(new Folder(parsedPath->at(parsedPath->size() - 1)));
        return;
    } catch (string exceptionStatement) {
        cerr << exceptionStatement << endl;
    }
}

void Terminal::chdir(string path) {
    vector<string> *parsedPath = parsePath(path);

    if (parsedPath->size() == 1 && parsedPath->at(0) == curFolder->getName()){
        return;
    }

    try {
        if (parsedPath->size() != 1){
            curFolder = getFolderXFromEnd(parsedPath,0);
            if (parsedPath->at(0) == root->getName()) {
                curFolderPath = path;
            } else {
                for (unsigned int i = 1; i < parsedPath->size(); i++) {
                    curFolderPath += "/" + parsedPath->at(i);
                }
            }
        } else if (parsedPath->at(0) == root->getName()){
            curFolder = root;
            curFolderPath = root->getName();
        } else {
            throw noSuchFolder();
        }
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
}

void Terminal::pwd() const {
    outputStream << curFolderPath << "/" << endl;
}

void Terminal::ls(string path) {
    vector<string> *parsedPath = parsePath(path);

    if (parsedPath->at(0) == "."){
        printFolder(curFolder);
    } else {
        if (path[path.length() - 1] != '/') {
            path += '/';
        }
        if (path == root->getName() + "/") {
            outputStream << path + ":" << endl;
            printFolder(root);
        } else if (path == curFolder->getName() + "/") {
            outputStream << path + ":" << endl;
            printFolder(curFolder);
        } else {
            try {
                Folder *f = getFolder(path);
                outputStream << path + ":" << endl;
                printFolder(f);
            } catch (string exceptionStatement) {
                cerr << exceptionStatement << endl;
            }
        }
    }
}

void Terminal::rmdir(string path) {
    vector<string> *parsedPath = parsePath(path);
    string toRemove = parsedPath->at(parsedPath->size()-1);
    try {
        Folder *toRemoveFatherFolder = getFolderXFromEnd(parsedPath, 1);

        if (toRemoveFatherFolder->folderExists(toRemove)) {
            toRemoveFatherFolder->deleteFolder(toRemove);
        } else {
            throw noSuchFolder();
        }
    } catch (string exceptionStatement){
        cerr << exceptionStatement << endl;
    }
}

void Terminal::lproot() const {

}

void Terminal::touch( string path) {
    try {
        Folder *f;
        vector<string> *parsedPath = parsePath(path);

        if (parsedPath->size() == 1) {
            if (curFolder->fileExists(parsedPath->at(0))) {
                curFolder->getFile(parsedPath->at(0))->touch();
            } else {
                curFolder->getFiles().push_back(new File(parsedPath->at(0)));
            }
            return;
        }

        f = getFolderXFromEnd(parsedPath,1);

        if (f->fileExists(parsedPath->at(parsedPath->size()-1))){
            f->getFile(parsedPath->at(parsedPath->size()-1))->touch();
        } else {
            f->getFiles().push_back(new File(parsedPath->at(parsedPath->size() - 1)));
        }
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

string Terminal::getCurFolderPath() const {
    return "amichai@miniterminal:~/" + curFolderPath;
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

string Terminal::folderAlreadyExists() {
    return "ERROR: folder already exists";
}

Folder *Terminal::getFolderXFromEnd(vector<string> *parsedPath, unsigned int posFromEnd) {
    Folder *f;
    if (parsedPath->at(0) == root->getName()) {
        f = root;
    } else if (parsedPath->at(0) == curFolder->getName()) {
        f = curFolder;
    } else {
        throw noSuchFolder();
    }

    if (parsedPath->size() > 1+posFromEnd) {
        vector<string>::iterator curFolderIterator = parsedPath->begin();
        curFolderIterator++;

        for (unsigned int i = 0; i < parsedPath->size()-1 -posFromEnd; i++) {
            if (f->hasFolder(*curFolderIterator)) {
                f = f->getFolder(*curFolderIterator);
                curFolderIterator++;
            } else {
                throw noSuchFolder();
            }
        }
    }
    return f;
}