
/*  COMP.CS.100 Project 3: Orienteering
 *
 * class : point
 *
 *
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Elias Nikkinen
 * Opiskelijanumero: 50497168
 * Käyttäjätunnus: shelni
 * E-Mail: elias.nikkinen@tuni.fi
 *
 * */
#ifndef POINT_HH
#define POINT_HH

#include <string>

class Point
{
public:
    Point(std::string name, int x, int y, int height, char marker);

    std::string name() const;
    int x() const;
    int y() const;
    int height() const;
    char marker() const;

private:
    std::string name_;
    int getX_;
    int getY_;
    int height_;
    char marker_;


};

#endif // POINT_HH
