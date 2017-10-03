#include <memory>
#include "checker.h"
#include "king.h"
#include "players_statics.h"

#pragma once

#define BOARD_SIZE 8

#define GENERAL_MOVEMENT_ERROR 0
#define PIECE_OBSTRUCTION_ERROR 1
#define OUT_OF_BOUNDS_ERROR 2
#define INVALID_COORDS_ERROR 3
#define LENGTH_NOT_VALID_ERROR 4
#define PIECE_OWNERSHIP_ERROR 5
#define OWN_PIECE_OBSTRUCTION_ERROR 6

namespace draughts {
    namespace model {
        
        class model;
        
        class checker;
        
        class king;
        
        class empty_space;
        
        class board {
            
            static std::unique_ptr<board> instance;
            
            board(void);
            
            std::vector<draughts::model::checker> checkers;
            
            
            public:
            
                static board * get_instance(void);
                static void delete_instance(void);
                
                void makeMove(int id, int startx, int starty, int endx, int endy)
                
                void executeMove(int id, int startx, int starty, int endx, int endy);
                
                void start_game(std::pair<draughts::model::player, draughts::model::player> players);
                
                int get_width() {
                    return BOARD_SIZE;
                }
                
                int get_height() {
                    return BOARD_SIZE;
                }
                
                void clearBoard(void);
                
                void populateRow(bool even, int row, char team, int playerId);
                
                char get_token(int x,int y);
                
                void removeCheckerAtLocation(int x, int y);
                
                class movePieceException: public std::exception
                {
                        public:
                            int errorType = 0;
                            movePieceException(int errorType) {
                                this->errorType = errorType;
                            }
                        
                            virtual const char* what() const throw()
                            {
                                if (this->errorType == OUT_OF_BOUNDS_ERROR) {
                                    return "At least one of the specified locations is out of bounds!";
                                }
                                else if (this->errorType == PIECE_OBSTRUCTION_ERROR) {
                                    return "There is a piece obstructing the move!";
                                }
                                else if (this->errorType == PIECE_OWNERSHIP_ERROR) {
                                    return "You do not own this piece!";
                                }
                                else if (this->errorType == INVALID_COORDS_ERROR) {
                                    return "Your coordinates are invalid!";
                                }
                                else if (this->errorType == LENGTH_NOT_VALID_ERROR) {
                                    return "Your coordinates are invalid! (Length not valid)";
                                }
                                else if (this->errorType == OWN_PIECE_OBSTRUCTION_ERROR) {
                                    return "You can't jump over your own piece!";
                                }
                                else {
                                    return "An error occurred while moving the piece!";
                                }
                            };
                        
                };
            
            private:
                checker *lastMoved;
        };
    }
}