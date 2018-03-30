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
    Terminal(ostream& out);                     //c'tor
    Terminal(const Terminal& rhs);              //copy c'tor
    Terminal& operator=(const Terminal& rhs);
    virtual ~Terminal();                        //d'tor

    void touch(string path);                                            //changes files time stamp
    void read(const string path, const int pos) ;                       //reads single character from chosen position
    void write(const string path, const size_t pos, const char val);    //writes single character to chosen postion
    void cat(const string path);                                        //prints files content
    void mkdir(string path);                                            //creates directory
    void chdir(string path);                                            //changes current directory
    void pwd() const;                                                   //prints current folders path
    void ls(string path);                                               //prints files contents
    bool copy(const string pathSource, const string pathDestination);   //copys file from source to destination
    void rmdir(string path);                                            //removes directory
    void lproot() const;                                                //prints all files and folders
    void ln(const string pathSource, const string pathDestination);     //created hard link between file in source and destination
    void wc(string path);                                               //prints number of words, lines and character in file
    void remove(string path);                                           //removes file
    void move(string pathSource, string pathDestination);               //moves file from source to destination

    ostream &getOutputStream() const;
    string getCurFolderPath() const;
    Folder *getRoot() const;

    struct noSuchFile : public exception {
        virtual const char* what() const throw(){
            return "ERROR: no such file";
        }
    };

    struct noSuchFolder : public exception{
        virtual const char* what() const throw() {
            return "ERROR: no such folder";
        }
    };

    struct folderAlreadyExists : public exception{
        virtual const char* what() const throw(){
            return "ERROR : folder already exists";
        }
    };
private:
    Folder* root;
    Folder* curFolder;
    ostream &outputStream;
    string curFolderPath;

    void printFolder(Folder *f) const;      //prints folder's content;
    Folder *getFolder(string folderPath);   //returns chosen folder
    vector<string> * parsePath(string path);    //breaks string containing path into vector containing parsed path
    Folder *getFolderXFromEnd(vector<string> *parsedPath, unsigned int posFromEnd); //receives vector with parsed path
                                                                                    //and returns the folder that is located
                                                                                    //x spots from end


};


#endif //EX1_TERMINAL_H
