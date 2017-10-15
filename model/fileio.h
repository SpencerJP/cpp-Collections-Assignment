/* 
    Spencer Porteous s3539519
    Jarod Wright s3601928
    C++ Assignment 2
*/

#include <iostream>
#include <fstream>
#include <exception>

#pragma once

namespace draughts
{

    namespace model
    {
        class model;
        
        class fileio {
                public:
                    std::string readFile(std::string filename);
                    void writeFile(std::string content, std::string filename);
                    
                    class fileNotFoundException: public std::exception
                        {
                        public:
                            virtual const char* what() const throw()
                            {
                                return "model::fileio: File is not found, or is empty!";
                            };
                        
                    };
                    
                    class couldNotCreateFileException: public std::exception
                        {
                        public:
                            virtual const char* what() const throw()
                            {
                                return "model::fileio: could not create file!";
                            };
                        
                    };
        };
        
    }
}