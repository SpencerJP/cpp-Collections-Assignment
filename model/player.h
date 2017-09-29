
class draughts {
    class model {
        class player {
            int score;
            int playernum;
            
            inline int player+(int a) {
                this.score = this.score + a;
            }
            
            inline int player++() {
                this.score = this.score + 1;
            }
            
        };
    };
};