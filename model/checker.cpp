#include "checker.h"



draughts::model::checker::checker(void) {
}

char draughts::model::checker::getPieceChar(void) {
    return team;
}

std::vector<std::pair<int,int>> draughts::model::checker::possibleDirections(std::vector<checker> checkers) {
    std::vector<std::pair<int,int>> moves;
    std::pair<int,int> topLeft = std::make_pair<int,int>(-1,1);
    std::pair<int,int> topRight = std::make_pair<int,int>(1,1);
    
    // also if you can take a piece then that's valid too
    // TODO 
    
    for(auto piece : checkers) {
        // check if topleft has a piece
        if(piece.isAtLocation(topLeft) && (piece.team != this->team)) {
            moves.push_back(std::make_pair<int, int>(-2,2));
        } else {
            moves.push_back(topLeft);
        }
        // check if topright has a piece
        if(piece.isAtLocation(topRight) && (piece.team != this->team)) {
            moves.push_back(std::make_pair<int, int>(2,2));
        } else {
            moves.push_back(topRight);
        }
    }
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

bool draughts::model::checker::isAtLocation(std::pair<int, int> coords) {
    if ((this->x != coords.first) || (this->y != coords.second)) {
        return false;
    }
    
    return true;
}