//
// Created by amichai on 24/03/18.
//

#include <sstream>
#include "Terminal.h"

Terminal::Terminal(ostream &output)
:outputStream(output), root(new Folder("V/")),curFolderPath("V/"),curFolder(root) {
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

void Terminal::mkdir(const string path) {

}

void Terminal::chdir(const string path) const {

}

void Terminal::pwd() const {
    outputStream << curFolderPath << endl;
}

void Terminal::ls() const {
    for (vector<Folder*>::iterator i = curFolder->getFirstFolder(); i != curFolder->getLastFolder(); i++){
        outputStream << (*i)->getName() << endl;
    }

    for (vector<File*>::iterator i = curFolder->getFirstFile(); i != curFolder->getLastFile(); i++){
        outputStream << (*i)->getName() << endl;
    }
}

void Terminal::rmdir(const string path) {

}

void Terminal::lproot() const {

}

void Terminal::touch(const string path) {
    stringstream s(path);
    string parsedPath;

    getline(s,parsedPath,'/');
    getline(s,parsedPath,'/');
    while (s.eofbit){
        if (parsedPathIsInFiles(parsedPath)){
            curFolder->getFile(parsedPath)->touch();
            return;
        }
        if (parsedPathIsInFolders(parsedPath)){
            curFolder = curFolder->getFolder(parsedPath);
        } else {
            curFolder->getFiles().push_back(new File(parsedPath));
            outputStream << "added " + parsedPath << endl;
            return;
        }
        getline(s,parsedPath,'/');
    }

    curFolder->getFiles().push_back(new File(parsedPath));
    outputStream << "added " + parsedPath << endl;
    curFolder = root;
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

string Terminal::parseFileName(string path) {
    stringstream s(path);
    string fileName;
    getline(s,fileName,'/');
    getline(s,fileName,'/');

    return fileName;
}

bool Terminal::parsedPathIsInFiles(const string parsedPath) {
    return curFolder->fileExists(parsedPath);
}

bool Terminal::parsedPathIsInFolders(const string parsedPath) {
    return curFolder->folderExists(parsedPath);
}
