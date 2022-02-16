/* Hitori
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa vain yksi tai ei yhtään. Kuitenkaan
 * vierekkäisten ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero (ruutu) saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Elias Nikkinen
 * Opiskelijanumero: 50497168
 * Käyttäjätunnus: shelni
 * E-Mail: elias.nikkinen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Funktioon check_islands on saatu apua
 * Discordin "yleinen" -kanavalta.
 * */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// vektori jonka sisällä on vektori
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

// Kysyy käyttäjältä pelilaudan tulostusmenetelmän
// ja täyttää pelilaudan käyttäjän valitseman menetelmän
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
                // puskee rivin jokaisella loopilla
                gameboard.push_back(std::vector<int>());
                for(unsigned int x = 0; x < BOARD_SIDE; ++x ) {
                    // puskee sarakkeen jokaisella looppauksella
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
// tarkistaa onko viereinen tai ylhäällä/alhaalla oleva
// elementti tyhjä
bool check_loss(Gameboard& gameboard, int y, int x){
    if ((y-1 == 0 || gameboard.at(y-2).at(x-1) != 0)
            && (y-1 == BOARD_SIDE-1 || gameboard.at(y).at(x-1) != 0)
            && (x-1 == 0 || gameboard.at(y-1).at(x-2) != 0)
            && (x-1 == BOARD_SIDE-1 || gameboard.at(y-1).at(x) != 0)){
        return true;
    }
    return false;
}

// loopissa count -funktioilla lasketaan lukujen 1 2 3 4 5
// määrät jos kaikkien lukujen määrä on rivillä 0 tai 1, pusketaan
// 1 väliaikaiseen vektoriin. Jos väliaikaisessa vektorissa yhden
// määrä on 5, on peli voitettu
bool check_rows(Gameboard& gameboard){
    int x1, x2, x3, x4, x5;
    std::vector< int > arr;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i){
        x1 = count(gameboard[i].begin(), gameboard[i].end(),1);
        x2 = count(gameboard[i].begin(), gameboard[i].end(),2);
        x3 = count(gameboard[i].begin(), gameboard[i].end(),3);
        x4 = count(gameboard[i].begin(), gameboard[i].end(),4);
        x5 = count(gameboard[i].begin(), gameboard[i].end(),5);
        if(x1 < 2 and x2 < 2 and x3 < 2 and x4 < 2 and x5 < 2){
            arr.push_back(1);
        } else {
            return false;
        }
    }
    if (count(arr.begin(), arr.end(), 1) == 5) {
        return true;
    }
    return false;
}

// tekee 2-ulotteiselle vektorille transpoosin ja tarkastaa
// että jokainen rivi on erilainen eli samanlailla miten
// ylempi
bool transpose_and_check_rows(Gameboard& gameboard){
    if (gameboard.size() == 0)
        return false;
    Gameboard trans_vec(gameboard[0].size(), vector<int>());
    for(unsigned int i = 0; i < gameboard.size(); i++){
        for(unsigned int j = 0; j < gameboard[i].size(); j++){
            trans_vec[j].push_back(gameboard[i][j]);
        }
    }
    int x1, x2, x3, x4, x5;
    std::vector< int > arr;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i){
        x1 = count(gameboard[i].begin(), gameboard[i].end(),1);
        x2 = count(gameboard[i].begin(), gameboard[i].end(),2);
        x3 = count(gameboard[i].begin(), gameboard[i].end(),3);
        x4 = count(gameboard[i].begin(), gameboard[i].end(),4);
        x5 = count(gameboard[i].begin(), gameboard[i].end(),5);
        if(x1 < 2 and x2 < 2 and x3 < 2 and x4 < 2 and x5 < 2){
            arr.push_back(1);
        } else {
            return false;
        }
    }
    if (count(arr.begin(), arr.end(), 1) == 5) {
        return true;
    }
    return false;

}

// Käy 2-ulotteisen vektorin elementit läpi laskien
// kuinka monta ruutu on tyhänä elementin ympärillä on
// Peli on hävitty jos elementin ympärillä on jossain kohtaa
// pelkkää nollaa eli tyhjää. Apua sain tähän Discordissa
// "yleinen" kanavalta.
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

// poistaa pelilaudalta elementin(numeron) ja
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

                // käydään voitto- ja häviötilanteet läpi. + muut.
                if(0 < x and x <= BOARD_SIDE and 0 < y and y <= BOARD_SIDE) {
                    if(gameboard.at(y -1).at(x-1) == 0){
                        cout << "Already removed" << endl;;
                        continue;
                    }
                    // poistaa elementin pelilaudasta, jonka jälkeen
                    // tulostaa muuttuneen pelilaudan

                    if (check_loss(gameboard,y,x) == true) {
                        gameboard.at(y - 1).at(x - 1) = 0;

                        // kutsuu funktiota, jossa tarkastetaan
                        // saaret
                        if (check_island(gameboard) == true){
                            print(gameboard);
                            cout << "You lost" << endl;
                            return;
                        }
                        // jos 2-ulotteisen vektorin rivin elementit
                        // ovat erilaiset ja sen transpoosin elementit
                        // ovat erilaiset, peli on voitettu
                        if (check_rows(gameboard) == true and transpose_and_check_rows(gameboard) == true){
                            print(gameboard);
                            cout << "You won" << endl;
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
