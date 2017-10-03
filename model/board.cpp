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

    //Populate vector available with all pieces on your team that can take an enemy piece
    std::vector<draughts::model::checker> available;
    for (draughts::model::checker c : checkers) {
        if (c.playerId == id) {
            for (std::pair<int,int> dir : c.possibleDirections()) {
                std::pair<int, int> adj_loc = std::make_pair(startx + dir.first, starty + dir.second); //Location of adjacent spot  
                for (draughts::model::checker d : checkers) {
                    if (d.isAtLocation(adj_loc)) {
                        if (d.playerId == id)
                            continue;
                        std::pair<int, int> att_loc = std::make_pair(adj_loc.first * 2, adj_loc.second * 2);
                        bool canTake = true;
                        for (draughts::model::checker e : checkers) {
                            if (e.isAtLocation(att_loc)) {
                                canTake = false;
                                break;
                            }
                        }
                        if (canTake)
                            available.push_back(c);
                        break;
                    }
                }
            }
        }
    }
    
    std::vector<draughts::model::checker> searchSpace = available;
    if (available.empty())
        searchSpace = checkers;
        
    for (draughts::model::checker selected : searchSpace) {
        if (selected.isAtLocation(startx,starty) && selected.playerId == id) {  //Makes sure player moving piece owns piece
            for (std::pair<int,int> dir : selected.possibleDirections()) {  //Gets direction piece can move
                if (dirx / dir.first > 0 && diry / dir.second > 0) {    //Makes sure that the direction is correct
                    std::pair<int, int> adj_loc = std::make_pair(startx + dir.first, starty + dir.second); //Location of adjacent spot
                    for (draughts::model::checker d : checkers) { 
                        if (d.isAtLocation(adj_loc)) {  //Checks if there is a piece at the adjacent spot
                            if (d.playerId == id) { //Can't jump over your own piece?
                                //FAILURE
                                return;
                            }
                            
                            std::pair<int, int> att_loc = std::make_pair(adj_loc.first * 2, adj_loc.second * 2);  //Location of attack location
                            for (draughts::model::checker e : checkers) {
                                if (e.isAtLocation(att_loc)) {    //Checks if there is a piece at the attack location
                                    //FAILURE
                                    return;
                                }
                            }
                            
                            if (endx == att_loc.first && endy == att_loc.second) {  //Checks that the free space is the desired location
                                //now check whether player has to chain moves
                                for (std::pair<int,int> dir : selected.possibleDirections()) {
                                    std::pair<int, int> adj_loc2 = std::make_pair(startx + dir.first, starty + dir.second); //Location of adjacent spot  
                                    for (draughts::model::checker d : checkers) {
                                        if (d.isAtLocation(adj_loc2)) {
                                            if (d.playerId == id)
                                                continue;
                                            std::pair<int, int> att_loc2 = std::make_pair(adj_loc2.first * 2, adj_loc2.second * 2);
                                            bool canTake = true;
                                            for (draughts::model::checker e : checkers) {
                                                if (e.isAtLocation(att_loc2)) {
                                                    canTake = false;
                                                    break;
                                                }
                                            }
                                            if (canTake) {
                                                //SUCCESS, player must chain moves
                                                executeMove(id, startx, starty, endx, endy);
                                                return;
                                            }
                                        }
                                    }
                                }
                                //SUCCESS, player can't chain moves
                                executeMove(id, startx, starty, endx, endy);
                                return;
                            }
                        }
                    }
                    if (endx == adj_loc.first && endy == adj_loc.second) {  //Checks that the free space is the desired location
                        executeMove(id, startx, starty, endx, endy);
                        //SUCCESs
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
}

void draughts::model::board::executeMove(int id, int startx, int starty, int endx, int endy) {
    
    draughts::model::checker * checkerToMove;
    for(auto checker : this->checkers) {
        if(checker.isAtLocation(startx, starty)) {
            checkerToMove = &checker;
            break;
        }
    }
    int row = (checkerToMove->team == 'x') ? 8 : 1
    if (std::abs(endx) == 1) { // TODO REMOVE C FUNCTION, REPLACE WITH STDLIB.
        if (endx != row) {
            checkerToMove->setLocation(endx, endy);
        } else {
            draughts::model::king temp;
            temp.setLocation(endx, endy);
            temp << team;
            checkers.push_back(temp);
            this->checkers.erase(std::remove( this->checkers.begin(),  this->checkers.end(), *checkerToMove), this->checkers.end());
            
        }
        
    }
    else {
        draughts::model::checker * checkerToDestroy;
        for(auto checker : this->checkers) {
            if(checker.isAtLocation(startx + endx, starty)) {
                checkerToDestroy = &checker;
                break;
            }
        }
        this->checkers.erase(std::remove( this->checkers.begin(),  this->checkers.end(), *checkerToDestroy), this->checkers.end());
        draughts::model::model::get_instance()->currentPlayers.first.playernum == id ? draughts::model::model::get_instance()->currentPlayers.first++ : draughts::model::model::get_instance()->currentPlayers.second++
        
        if (endx != row) {
            checkerToMove->setLocation(endx, endy);
        } else {
            draughts::model::king temp;
            temp.setLocation(endx, endy);
            temp << team;
            checkers.push_back(temp);
            this->checkers.erase(std::remove( this->checkers.begin(),  this->checkers.end(), *checkerToMove), this->checkers.end());
            
        }
    }
    
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