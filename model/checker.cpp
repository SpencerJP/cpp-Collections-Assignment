/* 
    Spencer Porteous s3539519
    Jarod Wright s3601928
    C++ Assignment 2
*/

#include "checker.h"

draughts::model::checker::checker(void) {
}

char draughts::model::checker::getPieceChar(void) {
    return team;
}

std::vector<std::pair<int,int>> draughts::model::checker::possibleDirections(void) {
    std::vector<std::pair<int,int>> moves;
    std::pair<int,int> left;
    std::pair<int,int> right;
    if (team == 'x') {
        left = std::make_pair<int,int>(-1,-1);
        right = std::make_pair<int,int>(1,-1);
    } else {
        left = std::make_pair<int,int>(-1,1);
        right = std::make_pair<int,int>(1,1);
    }
    moves.push_back(left);
    moves.push_back(right);
    return moves;
}
void draughts::model::checker::setLocation(int newx, int newy) {
    this->x = newx;
    this->y = newy;
}

bool draughts::model::checker::isAtLocation(int x, int y) {
    if ((this->x != x) || (this->y != y)) {
        return false;
    }
    
    return true;
}

bool draughts::model::checker::isAtLocation(std::pair<int, int> coords) {
    if ((this->x != coords.first) || (this->y != coords.second)) {
        return false;
    }
    
    return true;
}
