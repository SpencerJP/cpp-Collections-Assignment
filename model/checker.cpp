#include "checker.h"

draughts::model::checker::checker(char team) {
    this.team = team;
}

char draughts::model::checker::getPieceChar(void) {
    return team;
}

vector<pair<int,int>> draughts::model::checker::possibleDirections(void) {
    vector<pair<int,int>> moves;
    pair<int,int> topLeft = make_pair<int,int>(-1,1);
    pair<int,int> topRight = make_pair<int,int>(1,1);
    moves.push_back(topLeft);
    moves.push_back(topRight);
    return moves;
}