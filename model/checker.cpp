#include "checker.h"



draughts::model::checker::checker(void) {
}

char draughts::model::checker::getPieceChar(void) {
    return team;
}

std::vector<std::pair<int,int>> draughts::model::checker::possibleDirections(void) {
    std::vector<std::pair<int,int>> moves;
    std::pair<int,int> topLeft = std::make_pair<int,int>(-1,1);
    std::pair<int,int> topRight = std::make_pair<int,int>(1,1);
    
    // also if you can take a piece then that's valid too
    // TODO 
    
    moves.push_back(topLeft);
    moves.push_back(topRight);
    return moves;
}

void draughts::model::checker::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

bool draughts::model::checker::isAtLocation(int x, int y) {
    if ((this->x != x) || (this->y != y)) {
        return false;
    }
    
    return true;
}