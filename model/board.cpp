#include "board.h"

std::unique_ptr<draughts::model::board> draughts::model::board::instance =
nullptr;

draughts::model::board * draughts::model::board::get_instance(void)
{
    if(instance == nullptr)
    {
        instance = std::unique_ptr<board>(new board);	
    }
    return instance.get();    
}

void draughts::model::board::delete_instance(void)
{
    instance.reset(nullptr);
}

draughts::model::board::board(void) {
   
}

void draughts::model::board::start_game(void) {
    this->clearBoard();
    
    this->populateRow(true, 1, 'o');
    this->populateRow(false, 2, 'o');
    this->populateRow(true, 3, 'o');
    
    this->populateRow(true, 8, 'x');
    this->populateRow(false, 7, 'x');
    this->populateRow(true, 6, 'x');
}

void draughts::model::board::makeMove(int id, int startx, int starty, int endx, int endy) {
    
}

void draughts::model::board::populateRow(bool even, int row, char team) {
    if (even) {
        for (int i = 0; i < BOARD_SIZE; i = i+2) {
            
            draughts::model::checker checker;
            checker << team; // overloading operators example
            checker.setLocation(row, i);
            checkers.push_back(checker);
        }
    } else {
        for (int i = 1; i < BOARD_SIZE; i = i+2) {
            
            draughts::model::checker checker;
            checker << team;  // overloading operators example
            checker.setLocation(row, i);
            checkers.push_back(checker);
        }
    }
    return;
}

void draughts::model::board::clearBoard(void) {
    this->checkers.clear();
    /*
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            boardSpace[i][j] = draughts::model::checker('\0'); */
            
}

char draughts::model::board::get_token(int x, int y) {
    // TODO
    for(auto token : checkers) {
        if (token.isAtLocation(x, y)) {
            
            return token.team;
        }
    }
    return false;
}