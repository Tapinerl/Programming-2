#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';


//vektori jonka sisällä on vektori
using Gameboard = std::vector<std::vector<int>>;

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const Gameboard& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

//Kysyy käyttäjältä pelilaudan tulostusmenetelmän
//ja täyttää pelilaudan käyttäjän valitseman menetelmän
// mukaan.
bool startSelect(Gameboard& gameboard){
    default_random_engine rand_gen;

    string getInput = "";

    while (true){
        cout << "Select start (R for random, I for input): ";
        getline(cin, getInput);

        if (getInput == "R" or getInput == "r")
        {
            cout << "Enter seed value: ";
            string seed_value = "";
            getline(cin, seed_value);

            rand_gen.seed(stoi(seed_value));

            std::uniform_int_distribution<int> distribution(1, 5);
            for(unsigned int y = 0; y < BOARD_SIDE; ++y ) {
                //puskee rivin jokaisella loopilla
                gameboard.push_back(std::vector<int>());
                for(unsigned int x = 0; x < BOARD_SIDE; ++x ) {
                    //puskee sarakkeen jokaisella looppauksella
                    gameboard[y].push_back(distribution(rand_gen));
                }
            }
            break;
        }
        if (getInput == "I" or getInput == "i")
        {
            cout << "Input: ";
            string value1 = "";

            for (unsigned int y = 0; y < BOARD_SIDE; y++){
                // looppaa >> operaattoria ja puskee rivin
                if (value1 == "q"){
                    return false;
                }
                gameboard.push_back(std::vector<int>());
                for (unsigned int x = 0; x < BOARD_SIDE; x++) {
                    cin>>value1;
                    if(stoi_with_check(value1) == 0){
                        return false;
                    }
                    int temp = stoi_with_check(value1);
                    gameboard[y].push_back(temp);
                }
            }
            break;
        }
       if (getInput != "R" or getInput != "r" or getInput != "I" or getInput != "i"){
           continue;
       }
    }
    return true;
}

bool check_loss(Gameboard& gameboard, int y, int x){
    if ((y-1 == 0 || gameboard.at(y-2).at(x-1) != 0)
            && (y-1 == BOARD_SIDE-1 || gameboard.at(y).at(x-1) != 0)
            && (x-1 == 0 || gameboard.at(y-1).at(x-2) != 0)
            && (x-1 == BOARD_SIDE-1 || gameboard.at(y-1).at(x) != 0)){
        return true;
    }
    return false;
}

bool check_island(Gameboard& gameboard){
    int surr_nums;

    for (unsigned int y = 0; y < BOARD_SIDE; ++y){
        for (unsigned int x = 0; x < BOARD_SIDE; ++x){
            if (gameboard.at(y).at(x) == 0){
                continue;
            }
            surr_nums = 0;
            if (y != 0){
                if ( gameboard.at(y-1).at(x) != 0){
                    surr_nums += 1;
                }
            }
            if (x != 0){
                if (gameboard.at(y).at(x-1) != 0){
                    surr_nums += 1;
                }
            }
            if (y != BOARD_SIDE - 1){
                if(gameboard.at(y+1).at(x) != 0){
                    surr_nums += 1;
                }
            }
            if (x != BOARD_SIDE - 1){
                if(gameboard.at(y).at(x+1) != 0){
                    surr_nums += 1;
                }
            }
            if (surr_nums == 0){
                return true;
            }
        }
    }
    return false;
}


//poistaa pelilaudalta elementin(numeron) ja
// tulostaa laudan uudelleen
void remove_element(Gameboard& gameboard){
    string getInput_x = "";
    string getInput_y = "";
    while (true){
        cout << "Enter removable element (x, y): ";
        cin >> getInput_x;

        if (getInput_x == "q" or getInput_x == "Q"){
            cout << "Quitting" << endl;
            return;
        }
        else {
            cin >> getInput_y;
            if(stoi_with_check(getInput_x) == 0 or stoi_with_check(getInput_y) == 0){
                cout << "Out of board" << endl;
                continue;
            }
            else {
                unsigned int x = stoi_with_check(getInput_x);
                unsigned int y = stoi_with_check(getInput_y);

                if(0 < x and x <= BOARD_SIDE and 0 < y and y <= BOARD_SIDE) {
                    if(gameboard.at(y -1).at(x-1) == 0){
                        cout << "Already removed" << endl;;
                        continue;
                    }
                    //poistaa numeron pelilaudasta, jonka jälkeen
                    // tulostaa muuttuneen pelilaudan

                    if (check_loss(gameboard,y,x) == true) {
                        gameboard.at(y - 1).at(x - 1) = 0;
                        if (check_island(gameboard) == true){
                            print(gameboard);
                            cout << "You lost" << endl;
                            return;
                        }
                        print(gameboard);
                    }
                    else{
                        gameboard.at(y - 1).at(x - 1) = 0;
                        print(gameboard);
                        cout << "You lost" << endl;
                        return;
                    }
                }
                else{
                    cout << "Out of board" << endl;
                    continue;
                }
            }
        }
    }
}



int main()
{
    Gameboard gameboard;
    //jos antaa virheellisen syötteen tai syötteeksi "q"
    //kun kysytään käyttäjän inputtia
    // niin lopettaa ohjelman
    if (startSelect(gameboard) == false){
        return 0;
    }
    print(gameboard);
    remove_element(gameboard);


    return 0;
}
