#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
#include "fileio.h"
#include "players_statics.h"

#include <boost/tokenizer.hpp>

#pragma once

namespace draughts
{
    namespace model
    {
        class model
        {
            static std::unique_ptr<model> instance;

            model(void);

            public:
            int turnNumber; // amount of turns elapsed
            
            void start_game(int, int);
            char get_token(int,int);
            void make_move(int, int, int, int, int);

            void add_player(const std::string& );
            int get_player_score(int);
            std::string get_player_name(int);
            int get_current_player(void);
            std::map<int, std::string> get_player_list(void) const;
            int get_winner();
            int get_width();
            int get_height();
            static model * get_instance(void);
            static void delete_instance(void);
            virtual ~model(void);
        };
    }
}
