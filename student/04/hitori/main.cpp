#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';
const int SIZE = 5;


//vektori jonka sisälä on vektori
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
void startSelect(Gameboard& gameboard)
{
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
            for( int y = 0; y < SIZE; ++y ) {
                //puskee rivin jokaisella loopilla
                gameboard.push_back(std::vector<int>());
                for( int x = 0; x < SIZE; ++x ) {
                    //puskee sarakkeen jokaisella looppauksella
                    gameboard[y].push_back(distribution(rand_gen));
                }
            }
            break;
        }
        if (getInput == "I" or getInput == "i")
        {
            //lisää käyttäjän valitsemat luvut pelilautaan.
            cout << "Input: ";
            string value1 = "";

            for (unsigned int y = 0; y < BOARD_SIDE; y++){
                // looppaa >> operaattoria ja puskee rivin
                if (value1 == "q"){
                    break;
                }
                gameboard.push_back(std::vector<int>());
                for (unsigned int x = 0; x < BOARD_SIDE; x++) {
                    cin>>value1;
                    if(stoi_with_check(value1) == 0){
                        break;
                    }
                    else {
                        int temp = stoi_with_check(value1);
                        gameboard[y].push_back(temp);
                    }
                }
            }
            break;
        }

       if (getInput != "R" or getInput != "r" or getInput != "I" or getInput != "i")
       {
           continue;
       }
    }
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
                unsigned int y = stoi_with_check(getInput_x);
                unsigned int x = stoi_with_check(getInput_y);

                if(0 < x and x <= BOARD_SIDE and 0 < y and y <= BOARD_SIDE) {
                    if(gameboard.at(y -1).at(x-1) == 0){
                        cout << "Already removed" << endl;;
                        continue;
                    }
                    gameboard.at(y - 1).at(x - 1) = 0;
                    print(gameboard);
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

    startSelect(gameboard);
    print(gameboard);
    remove_element(gameboard);





    return 0;
}
