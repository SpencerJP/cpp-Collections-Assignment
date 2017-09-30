#include "model.h"

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
nullptr;


draughts::model::model::model(void) 
{
}

draughts::model::model * draughts::model::model::get_instance(void)
{
    if(instance == nullptr)
    {
        instance = std::unique_ptr<model>(new model);	
    }
    return instance.get();    
}

int draughts::model::model::get_player_score(int playernum)
{   
    
    return draughts::model::players::get_instance()->get_player_from_num(playernum).getScore();
}

void draughts::model::model::start_game(int plr1, int plr2)
{
    // TODO //
    draughts::model::player player1;
    draughts::model::player player2;
    player1.playernum = plr1;
    player2.playernum = plr2;
    this->turnNumber = 0;
    draughts::model::players::get_instance()->currentPlayers = std::make_pair(player1, player2);
    draughts::model::board * board = draughts::model::board::get_instance(); // initializes board
    board->start_game();
}

int draughts::model::model::get_winner()
{
    return EOF;
}

std::string draughts::model::model::get_player_name(int id)
{
    draughts::model::players players;
    return draughts::model::players::get_instance()->get_player_list()[id];
}

char draughts::model::model::get_token(int x ,int y)
{
    return draughts::model::board::get_instance()->get_token(x, y);
}

void draughts::model::model::make_move(int playernum,
        int startx, int starty, int endx, int endy)
{
}

std::map<int, std::string> draughts::model::model::get_player_list(void)
    const
{
    return draughts::model::players::get_instance()->get_player_list();
}

void draughts::model::model::add_player(const std::string& p)
{

    draughts::model::players::get_instance()->add_player(p);
}

int draughts::model::model::get_current_player(void)
{   
    return draughts::model::players::get_instance()->get_current_player(this->turnNumber);
}

void draughts::model::model::delete_instance(void)
{
    instance.reset(nullptr);
}


int draughts::model::model::get_width()
{
    return draughts::model::board::get_instance()->get_width();
}

int draughts::model::model::get_height()
{
    return draughts::model::board::get_instance()->get_height();
}

draughts::model::model::~model(void)
{
}

