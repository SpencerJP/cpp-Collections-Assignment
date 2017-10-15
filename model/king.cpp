/* 
    Spencer Porteous s3539519
    Jarod Wright s3601928
    C++ Assignment 2
*/

#include "king.h"

char draughts::model::king::getPieceChar(void) {
    return ((this->team == TEAM_ONE) ? TEAM_ONE_KING : TEAM_TWO_KING);
}

draughts::model::king::king(draughts::model::checker checker) {
    this->x = checker.x;
    this->y = checker.y;
    this->playerId = checker.playerId;
    this->team = checker.team;
}

std::vector<std::pair<int,int>> draughts::model::king::possibleDirections(void) {
    std::vector<std::pair<int,int>> moves;
    std::pair<int,int> topLeft = std::make_pair<int,int>(-1,1);
    std::pair<int,int> topRight = std::make_pair<int,int>(1,1);
    std::pair<int,int> bottomLeft = std::make_pair<int,int>(-1,-1);
    std::pair<int,int> bottomRight = std::make_pair<int,int>(1,-1);
    moves.push_back(topLeft);
    moves.push_back(topRight);
    moves.push_back(bottomLeft);
    moves.push_back(bottomRight);
    return moves;
}