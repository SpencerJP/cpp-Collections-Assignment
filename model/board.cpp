#include "board.h"

void draughts::model::board::board(void) {
    this.clearBoard();
    
    this.populateRow(true, 0, 'o');
    this.populateRow(false, 1, 'o');
    this.populateRow(true, 2, 'o');
    
    this.populateRow(true, 7, 'x');
    this.populateRow(false, 6, 'x');
    this.populateRow(true, 5, 'x');
}

void draughts::model::board::makeMove(int id, int startx, int starty, int endx, int endy) {
    
}

void draughts::model::board::populateRow(boolean even, int row, char team) {
    if (even)
        for (int i = 0; i < BOARD_SIZE; i = i+2)
            boardSpace[row][i] = new draughts::model::checker(team);
    else
        for (int i = 1; i < BOARD_SIZE; i = i+2)
            boardSpace[row][i] = new draughts::model::checker(team);
    return;
}

void draughts::model::board::clearBoard(void) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            boardSpace[i][j] = nullptr;
}