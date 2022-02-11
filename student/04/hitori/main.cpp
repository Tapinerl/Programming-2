#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';


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
            break;
        }
        if (getInput == "I" or getInput == "i")
        {
            cout << "Input: ";
            string user_input_number = "";
            getline(cin, user_input_number);

           //gameboard.push_back(CustomInput);
            break;
        }

       if (getInput != "R" or getInput != "r" or getInput != "I" or getInput != "i")
       {
           continue;
       }
    }
}



int main()
{
    Gameboard gameboard;

    startSelect(gameboard);
    print(gameboard);





    return 0;
}
