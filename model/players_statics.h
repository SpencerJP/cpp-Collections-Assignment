/* 
    Spencer Porteous s3539519
    Jarod Wright s3601928
    C++ Assignment 2
*/

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

#include "fileio.h"
#include "player.h"

#include <boost/tokenizer.hpp>

#pragma once

namespace draughts
{
    namespace model
    {
        class model;
        
        class fileio;
        
        class player;
        
        class players
        {
            static std::unique_ptr<players> instance;
            
            public:
                std::pair<draughts::model::player, draughts::model::player> currentPlayers;
                bool player_exists(const std::string&);
                void add_player(const std::string& );
                std::string get_player_name(int);
                
                int get_current_player(int x);
                draughts::model::player get_player_from_num(int);
                static players * get_instance(void);
                static void delete_instance(void);
                std::map<int, std::string> get_player_list(void) const;

                
        };
    }
}