#include "checker.h"
#define BOARD_SIZE 8

class Board {
    draughts::model::checker[BOARD_SIZE][BOARD_SIZE] boardSpace;
    public:
    void makeMove(int, int, int, int, int);
}