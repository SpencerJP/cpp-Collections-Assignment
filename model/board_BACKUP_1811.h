
#include <memory>
#include "checker.h"
#include "king.h"

#pragma once

#define BOARD_SIZE 8

<<<<<<< HEAD
class Board {
    draughts::model::checker[BOARD_SIZE][BOARD_SIZE] boardSpace;
    draughts::model::checker lastMoved;
    public:
    void makeMove(int, int, int, int, int);
=======
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
            void makeMove(int id, int startx, int starty, int endx, int endy);
            
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
            
        };
    }
>>>>>>> 3145d8480fdac8cbd0aa950eeeb3356714b31379
}