#include "king.h"

char draughts::model::king::getPieceChar(void) {
    return std::toupper(team);
}

vector<pair<int,int>> draughts::model::king::possibleDirections(void) {
    vector<pair<int,int>> moves;
    pair<int,int> topLeft = make_pair<int,int>(-1,1);
    pair<int,int> topRight = make_pair<int,int>(1,1);
    pair<int,int> bottomLeft = make_pair<int,int>(-1,-1);
    pair<int,int> bottomRight = make_pair<int,int>(1,-1);
    moves.push_back(topLeft);
    moves.push_back(topRight);
    moves.push_back(bottomLeft);
    moves.push_back(bottomRight);
    return moves;
}