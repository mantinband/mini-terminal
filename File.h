//
// Created by amichai on 24/03/18.
//

#ifndef EX1_FILE_H
#define EX1_FILE_H
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class File {
public:
    File(string fileName);                                                          //c'tor
    File(string fileName,ifstream *ifs, ofstream *ofs, int *numberOfReferences);    //c'tor for hard link
    File(const File& rhs);                                                          //copy c'tor
    File& operator=(const File& rhs);
    virtual ~File();                                                                //d'tor

    void operator[](pair<size_t, char> *posAndVal); //write single character to file. receives position and value
    const char operator[](size_t index);            //reads single character from specified position.

    void touch();                                   //updates files time stamp
    void remove();                                  //removes folder
    ostream &cat(ostream &out);                     //prints file content
    string wc();                                    //returns count of words, lines and characters
    File *copy(string &basicString);                //return a copy by value of current file


    const string &getName() const;
    ifstream *getIfs() const;
    ofstream *getOfs() const;

    int * getNumberOfReferences() const;
    char *getTimeSignature() const;


    class failedToOpenFile : exception {
        virtual const char* what() const throw() {
            return "ERROR: failed to open file";
        }
    };

    class failedToReadFromFile : exception {
        virtual const char* what() const throw() {
            return "ERROR: failed to read from file";
        }
    };

    class failedToWriteToFile : exception {
        virtual const char* what() const throw() {
            return "ERROR: failed to write to file";
        }
    };
private:
    string name;
    ifstream *ifs;
    ofstream *ofs;

    int *numberOfReferences;
    char *timeSignature;



    void updateTime();
    int numberOfWords();
    int numberOfLines();
    int numberOfChars();
};


#endif //EX1_FILE_H
