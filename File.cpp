//
// Created by amichai on 24/03/18.
//

#include "File.h"

const string &File::getName() const {
    return name;
}

void File::touch() {

}

File::File(string fileName):name(fileName) {

}
