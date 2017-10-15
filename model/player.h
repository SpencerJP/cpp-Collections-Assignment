/* 
    Spencer Porteous s3539519
    Jarod Wright s3601928
    C++ Assignment 2
*/

#include <cstdio>

#pragma once

namespace draughts {
    namespace model {
        class player {
            
            
            public:
            
                int playernum = EOF;
                int score = 0;
                
                int getScore(void) {
                    return this->score;
                }
                
                inline int operator+(int a) {
                    this->score = this->score + a;
                    return this->score;
                }
                
                inline int operator++() {
                    this->score = this->score + 1;
                    return this->score;
                }
                
                inline bool operator==(int a) {
                    return (a == this->playernum);
                }
        };
    }
}