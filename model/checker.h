#include <vector>

#pragma once

namespace draughts {
    namespace model {
        class checker {
    
            public:
            char team;
            int x;
            int y;
            checker(void);
            std::vector<std::pair<int,int>> possibleDirections(std::vector<checker> checkers);
            char getPieceChar(void);
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
