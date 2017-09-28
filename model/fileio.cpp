#include "fileio.h"

std::string draughts::model::fileio::readFile(std::string filename)
{
    std::string finalString = "";
    std::string s;
    std::ifstream inFile;
    
    inFile.open(filename);
    if (!inFile) {
        // throw exception
        throw draughts::model::fileio::fileNotFoundException();
    }
    
    while (inFile >> s) {
        finalString = finalString + s + " ";
    }
    
    inFile.close();
    if (finalString == "") {
        throw draughts::model::fileio::fileNotFoundException();
    }
    return finalString; 
}

void draughts::model::fileio::writeFile(std::string content, std::string filename)
{
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
        if (file.good()) {
            
        }
        else {
            throw draughts::model::fileio::couldNotCreateFileException();
        }
}