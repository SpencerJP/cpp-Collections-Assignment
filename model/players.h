#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

#include "fileio.h"

#include <boost/tokenizer.hpp>

#pragma once

namespace draughts
{
    namespace model
    {
        class model;
        
        class fileio;
        
        class players
        {
            public:
                bool player_exists(const std::string&);
                void add_player(const std::string& );
                int get_player_score(int);
                int get_current_player(void);
                std::string get_player_name(int);
                std::map<int, std::string> get_player_list(void) const;
        };
    }
}