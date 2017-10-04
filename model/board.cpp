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

void draughts::model::board::start_game(std::pair<draughts::model::player, draughts::model::player> players) {
    this->clearBoard();
    int id1 = players.first.playernum;
    int id2 = players.second.playernum;
    this->populateRow(true, 1, 'o', id2);
    this->populateRow(false, 2, 'o', id2);
    this->populateRow(true, 3, 'o', id2);
    
    this->populateRow(false, 8, 'x', id1);
    this->populateRow(true, 7, 'x', id1);
    this->populateRow(false, 6, 'x', id1);
}

int draughts::model::board::makeMove(int id, int startx, int starty, int endx, int endy) {
    
    int dirx = endx - startx;
    int diry = endy - starty;
    if (dirx % diry != 0) { //Makes sure direction is 45/135/225/315 degrees
        throw movePieceException(INVALID_COORDS_ERROR);
    }
    
    if (dirx > 2 || dirx < -2 || dirx == 0) { //Makes sure that the length of the move is valid
        throw movePieceException(LENGTH_NOT_VALID_ERROR);
    }
    
    if (endx < 0 || endx > 8 || endy < 0 || endy > 8) {
        throw movePieceException(INVALID_COORDS_ERROR);
    }

    //Populate vector available with all pieces on your team that can take an enemy piece
    std::vector<std::unique_ptr<draughts::model::checker>> available;
    for (auto && c : checkers) {
        if (c->playerId == id) {
            for (std::pair<int,int> dir : c->possibleDirections()) {
                std::pair<int, int> adj_loc = std::make_pair(startx + dir.first, starty + dir.second); //Location of adjacent spot  
                for (auto && d : checkers) {
                    if (d->isAtLocation(adj_loc)) {
                        if (d->playerId == id)
                            continue;
                        std::pair<int, int> att_loc = std::make_pair(adj_loc.first + dir.first, adj_loc.second + dir.second);
                        bool canTake = true;
                        for (auto && e : checkers) {
                            if (e->isAtLocation(att_loc)) {
                                canTake = false;
                                break;
                            }
                        }
                        if (canTake) {
                            std::unique_ptr<draughts::model::checker> tempPiece = std::make_unique<draughts::model::checker>(*(c.get()));
                            //temp->team = c->team;
                            //temp->playerId = c->team;
                            //temp->setLocation(c->x, c->y);
                            available.push_back(std::move(tempPiece));
                        }
                            
                        break;
                    }
                }
            }
        }
    }
    
    std::vector<std::unique_ptr<draughts::model::checker>> * searchSpace = &available;
    if (available.empty()) {
        searchSpace = &checkers;
    }
        
    for (auto && selected : (*searchSpace)) {
        // std::cout << "Selected: " << selected->x << ", " << selected->y << " | ID: " << selected->playerId << " | PlayerId: " << id << std::endl;
        if (selected->isAtLocation(startx,starty) && (selected->playerId == id)) {  //Makes sure player moving piece owns piece
            for (std::pair<int,int> dir : selected->possibleDirections()) {  //Gets direction piece can move
                // std::cout << "DIRS: " << dir.first << ", " << dir.second << std::endl;
                if (dirx / dir.first > 0 && diry / dir.second > 0) {    //Makes sure that the direction is correct
                    std::pair<int, int> adj_loc = std::make_pair(startx + dir.first, starty + dir.second); //Location of adjacent spot
                    // std::cout << "Checking: " << adj_loc.first << ", " << adj_loc.second << std::endl;
                    for (auto && d : checkers) { 
                        if (d->isAtLocation(adj_loc)) {  //Checks if there is a piece at the adjacent spot
                            if (d->playerId == id) { //Can't jump over your own piece?
                                throw movePieceException(OWN_PIECE_OBSTRUCTION_ERROR);
                            }
                            
                            std::pair<int, int> att_loc = std::make_pair(adj_loc.first + dir.first, adj_loc.second + dir.second);  //Location of attack location
                            for (auto && e : checkers) {
                                if (e->isAtLocation(att_loc)) {    //Checks if there is a piece at the attack location
                                    throw movePieceException(PIECE_OBSTRUCTION_ERROR);
                                }
                            }
                            
                            if (endx == att_loc.first && endy == att_loc.second) {  //Checks that the free space is the desired location
                                //now check whether player has to chain moves
                                for (std::pair<int,int> dir2 : selected->possibleDirections()) {
                                    std::pair<int, int> adj_loc2 = std::make_pair(endx + dir2.first, endy + dir2.second); //Location of adjacent spot  
                                    for (auto && d : checkers) {
                                        if (d->isAtLocation(adj_loc2)) {
                                            if (d->playerId == id)
                                                continue;
                                            std::pair<int, int> att_loc2 = std::make_pair(adj_loc2.first + dir2.first, adj_loc2.second + dir2.second);
                                            bool canTake = true;
                                            for (auto && e : checkers) {
                                                if (e->isAtLocation(att_loc2)) {
                                                    canTake = false;
                                                    break;
                                                }
                                            }
                                            if (canTake) {
                                                //SUCCESS, player must chain moves
                                                executeMove(id, startx, starty, endx, endy);
                                                return CHAIN_MOVE;
                                            }
                                        }
                                    }
                                }
                                //SUCCESS, player can't chain moves
                                executeMove(id, startx, starty, endx, endy);
                                return TOOK_PIECE;
                            }
                        }
                    }
                    if (endx == adj_loc.first && endy == adj_loc.second) {  //Checks that the free space is the desired location
                        executeMove(id, startx, starty, endx, endy);
                        //SUCCESS
                        return NORMAL_MOVE;
                    }
                }
            }
            throw movePieceException(PIECE_OWNERSHIP_ERROR);
        }
    }
    return NO_VALID_MOVES;
}

void draughts::model::board::populateRow(bool even, int row, char team, int playerId) {

    for (int i = ((even) ? 1 : 2); i <= BOARD_SIZE; i = i+2) {
        std::unique_ptr<draughts::model::checker> checker = std::make_unique<draughts::model::checker>();
        checker->team = team;
        checker->playerId = playerId;
        checker->setLocation(i, row);
        checkers.push_back(std::move(checker));
    }

    return;
}

void draughts::model::board::clearBoard(void) {
    this->checkers.clear();
}

void draughts::model::board::executeMove(int id, int startx, int starty, int endx, int endy) {
    
    
    int row = ((get_token(startx, starty) == 'x') ? 1 : 8);
    if (std::abs(starty - endy) == 1) { // TODO REMOVE C FUNCTION, REPLACE WITH STDLIB.
        if (endy != row) {
            for(auto && piece : this->checkers) {
                if(piece->isAtLocation(startx, starty)) {
                    piece->setLocation(endx, endy);
                    break;
                }
            }
        } else {
            draughts::model::checker * checkerToMove;
            for(auto && piece : this->checkers) {
                if(piece->isAtLocation(startx, starty)) {
                    checkerToMove = piece.get();
                    break;
                }
            }
            std::unique_ptr<draughts::model::checker> temp = std::make_unique<draughts::model::king>(*checkerToMove);
            for (auto && piece : checkers) {
                if (piece->isAtLocation(startx, starty)) {
                    temp->team = piece->team;
                    temp->playerId = piece->playerId;
                    std::cout << temp->playerId << std::endl;
                    std::cout << temp->team << std::endl;
                    std::cout << id << std::endl;
                    break;
                }
            }
            temp->setLocation(endx, endy);
            removeCheckerAtLocation(startx, starty);
            checkers.push_back(std::move(temp));
        }
        
    }
    else {
        for(auto && checker : this->checkers) {
            if(checker->isAtLocation( startx + (1 * (startx > endx ? -1 : 1)), starty + (1 * (starty > endy ? -1 : 1))) ) {
                removeCheckerAtLocation( startx + (1 * (startx > endx ? -1 : 1)), starty + (1 * (starty > endy ? -1 : 1)));
                break;
            }
        }
        /* TODO add score here */
        
        if (endx != row) {
            for(auto && piece : this->checkers) {
                if(piece->isAtLocation(startx, starty)) {
                    piece->setLocation(endx, endy);
                    break;
                }
            }
        } else {
            draughts::model::checker * checkerToMove;
            for(auto && piece : this->checkers) {
                if(piece->isAtLocation(startx, starty)) {
                    checkerToMove = piece.get();
                    break;
                }
            }
            std::unique_ptr<draughts::model::checker> temp = std::make_unique<draughts::model::king>(*checkerToMove);
            temp->setLocation(endx, endy);
            checkers.push_back(std::move(temp));
            removeCheckerAtLocation(startx, starty);
        }
    }
    
} 

char draughts::model::board::get_token(int x, int y) {
    for(auto && token : checkers) {
        if (token->isAtLocation(y, x)) {
            
            return token->getPieceChar();
        }
    }
    return ' ';
}

void draughts::model::board::removeCheckerAtLocation(int x, int y) {
    int index = 0;
    for(auto && piece : checkers) {
        if(piece->isAtLocation(x, y)) {
            break;
        }
        index++;
    }
    std::cout << "meme2" << std::endl;
    checkers.erase(checkers.begin() + index);
}

bool draughts::model::board::bothTeamsStillHavePieces() {
    bool x_stillHasPieces = false; 
    bool o_stillHasPieces = false;
    for(auto && piece : checkers) {
        if (piece->team == 'x') {
            x_stillHasPieces = true; 
        } else {
            o_stillHasPieces = true; 
        }
    }
    return !(x_stillHasPieces && o_stillHasPieces);
}