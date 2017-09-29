#include "players.h"

void draughts::model::players::add_player(const std::string& p)
{
    std::map<int, std::string> playersList;
    std::string toWrite = "";
    if (draughts::model::players::player_exists(p)) {
        throw std::runtime_error(std::string("model::model: player exists!"));
    }
    try {
        std::cout << "get_player_list: " << std::endl;
        playersList = draughts::model::players::get_player_list();
        std::cout << "get_player_list done " << std::endl;
        int i = playersList.size() + 1;
        playersList[i] = p;
    }
    catch(std::exception &ex) {
        playersList = std::map<int,std::string>();
        playersList[1] = p;
    }
    for(auto const &player : playersList) {
        std::cout << player.first << " " << player.second << std::endl;
        toWrite = toWrite + player.second + ";";
    }
    draughts::model::fileio fileio;
    fileio.writeFile(toWrite, "players.txt");
    
}

bool draughts::model::players::player_exists(const std::string& pname)
{
    try {
        
        draughts::model::fileio fileio;
        std::string playersFile = fileio.readFile("players.txt");
    }
    catch(std::exception& ex)
    {
        return false; // file doesn't exist so we don't have any players at all
    }
    std::map<int, std::string> playerList = draughts::model::players::get_player_list();
    for(auto const &player : playerList) {
        if(player.second == pname) {
            return true;
        }
    }
    return false;
}

int draughts::model::players::get_current_player(void)
{
    
    return EOF;
}

std::map<int, std::string> draughts::model::players::get_player_list(void) 
    const
{
    std::map<int, std::string> nameslist;
    std::string playersFile;
    
    draughts::model::fileio fileio;
    
    playersFile = fileio.readFile("players.txt"); // throws if file doesn't exist
    
    std::istringstream is(playersFile);
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer; // make it shorter to type
    std::string line;
    boost::char_separator<char> sep(";");    //CSV format
        
        while (getline(is, line)) {
            tokenizer t(line, sep);
            int i = 1;
            
            for (tokenizer::iterator it = t.begin(); it != t.end(); ++it) {
                if ((*it == "") || (*it == " ")) { // hack to fix strange bug
                    continue;
                }
                std::cout << "*it: " << *it << std::endl;
                nameslist[i] = *it;
            }
        }
    
    return nameslist;
}
