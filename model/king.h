#include <vector>
#include "checker.h"

#pragma once

#define TEAM_ONE 'x'
#define TEAM_TWO 'o'
#define TEAM_ONE_KING 'X'
#define TEAM_TWO_KING 'O'

namespace draughts {
    namespace model {
        
        class king : public checker{
            public:
                king(checker);
                // std::vector<std::pair<int,int>> possibleDirections(std::vector<checker> checkers);
                std::vector<std::pair<int,int>> possibleDirections(void) override;
                char getPieceChar(void) override; 
        };
    }
}