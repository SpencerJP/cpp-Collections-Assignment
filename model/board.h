
#include <memory>
#include "checker.h"
#include "king.h"
#include "players_statics.h"

#pragma once

#define BOARD_SIZE 8

#define GENERAL_MOVEMENT_ERROR 0
#define PIECE_OBSTRUCTION_ERROR 1
#define OUT_OF_BOUNDS_ERROR 2

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
        
            char get_token(int x ,int y);
                static board * get_instance(void);
                static void delete_instance(void);
                
                void makeMove(int id, int startx, int starty, int endx, int endy);
                
                void executeMove(int id, int startx, int starty, int endx, int endy)
                
                void start_game(void);
                
                int get_width() {
                    return BOARD_SIZE;
                }
                
                int get_height() {
                    return BOARD_SIZE;
                }
                
                void clearBoard(void);
                
                void populateRow(bool even, int row, char team);
                
                char get_token(int x ,int y);
                
                class movePieceException: public std::exception
                {
                        movePieceException(int errorType) {
                            this->errorType = errorType;
                        }
                        int errorType = GENERAL_MOVEMENT_ERROR;
                        public:
                            virtual const char* what() const throw()
                            {
                                if (this->errorType == OUT_OF_BOUNDS_ERROR) {
                                    return "At least one of the specified locations is out of bounds!";
                                }
                                else if (this->errorType == PIECE_OBSTRUCTION_ERROR) {
                                    return "There is a piece obstructing the move!";
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