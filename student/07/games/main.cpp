/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 * EXAMPLE SOLUTION
 * ===============================
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>

using GAMES = std::map<std::string, std::map<std::string, int>>;

//keksi paremmat nimet?
//merkkijonovakioita
const std::string FILE_NOT_READ_TEXT = "Error: File could not be read.",
                  INPUT_FILE_PROMPT = "Give a name for input file: ",
                  FILE_FORMAT_INVALID_TEXT = "Error: Invalid format in file.";

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

bool line_is_ok(std::vector<std::string> const &line_parts){
    // vektori on kolmiosainen = ; oli tasan kaksi kpl




    // return true, kun plein ja pelaajan nimi eivät ole tyhjiä
    return line_parts.size() == 3 && !line_parts.at(0).empty() && !line_parts.at(1).empty();
}

bool read_file_input(GAMES &scoreboard){
    //haetaan tiedostonimi
    std::string filename = "";
    std::cout << INPUT_FILE_PROMPT;
    std::getline(std::cin, filename);

    //avaa teidosto ja tarkista
    std::ifstream file(filename);

    if(!file){
        std::cout << FILE_NOT_READ_TEXT << std::endl;
        return false;

    }
    //käydään tiedosto läpi ja tarkastetaan syöte
    std::string line = "";
    std::vector<std::string> line_parts;

    while(std::getline(file, line)){
        line_parts = split(line);
        if(!line_is_ok(line_parts)){
            std::cout << FILE_FORMAT_INVALID_TEXT << std::endl;
            file.close();
            return false;
        }

        // indeksi=0: peli, indeksi=1: pelaaja, indeksi=2: pistemäärä
        std::string gamename = line_parts.at(0), player = line_parts.at(1), points_str = line_parts.at(2);
        //tarkista onko peli tietokannassa
        if(scoreboard.find(gamename) == scoreboard.end()){
            scoreboard.insert({gamename, {}});
        }

        // lisätään pelaajan pisteet tietokantaan
        scoreboard.at(gamename).insert({player, std::stoi(points_str)});

    }
    return true;

}



int main()
{
    //peli > pelaaja > pisteet
    //tietorakenne
    GAMES scoreboard;

    //luetaan tiedostosyöte
    if(!read_file_input(scoreboard)) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
