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
    for (draughts::model::checker c : checkers) {
        if (c.isAtLocation(startx,starty) && c.playerId == id) {  //Makes sure player moving piece owns piece
        
            int dirx = startx - endx;
            int diry = starty - endy;
            
            if (dirx % diry != 0) { //Makes sure direction is 45/135/225/315 degrees
                //FAILURE
                return;
            }
            
            if (dirx > 2 || dirx < -2 || dirx == 0) { //Makes sure that the length of the move is valid
                //FAILURE
                return;
            }
        
            for (std::pair<int,int> dir : c.possibleDirections()) {  //Gets direction piece can move
                if (dirx / dir.first > 0 && diry / dir.second > 0) {    //Makes sure that the direction is correct
                    std::pair<int, int> adj_loc = std::make_pair(startx + dir.first, starty + dir.second); //Location of adjacent spot
                    for (draughts::model::checker d : checkers) { 
                        if (d.isAtLocation(adj_loc)) {  //Checks if there is a piece at the adjacent spot
                            std::pair<int, int> att_loc = std::make_pair(adj_loc.first * 2, adj_loc.second * 2);  //Location of attack location
                            for (draughts::model::checker e : checkers) {
                                if (e.isAtLocation(att_loc)) {    //Checks if there is a piece at the attack location
                                    //FAILURE
                                    return;
                                }
                            }
                            if (endx == att_loc.first && endy == att_loc.second) {  //Checks that the free space is the desired location
                                //SUCCESS
                                return;
                            }
                        }
                    }
                    if (endx == adj_loc.first && endy == adj_loc.second) {  //Checks that the free space is the desired location
                        //SUCCESS
                        return;
                    }
                }
            }
            //FAILURE: NOT FOUND
            return;
        }
    }
    //FAILURE: NOT FOUND
    return;
}

void draughts::model::board::populateRow(bool even, int row, char team) {

    for (int i = ((even) ? 0 : 1); i <= BOARD_SIZE; i = i+2) {
        draughts::model::checker checker;
        checker << team; // overloading operators example
        checker.setLocation(row, i);
        checkers.push_back(checker);
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
    return ' ';
}