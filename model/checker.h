#include <vector>

#pragma once

namespace draughts {
    namespace model {
        class checker {
    
            public:
                int playerId;
                char team;
                int x;
                int y;
                checker(void);
                // std::vector<std::pair<int,int>> possibleDirections(std::vector<checker> checkers);
                virtual std::vector<std::pair<int,int>> possibleDirections(void);
                virtual char getPieceChar(void);
                void setLocation(int x, int y);
                bool isAtLocation(int x, int y);
                bool isAtLocation(std::pair<int, int> coords);
                
                char operator<<(char x) {
                    this->team = x;
                    return this->team;
                }
        };
    }
}
