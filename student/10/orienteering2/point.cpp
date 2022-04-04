
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
#include "point.hh"
#include <iostream>


Point::Point(std::string name, int x, int y, int height, char marker) :
             name_(name), getX_(x), getY_(y), height_(height), marker_(marker)
{}

std::string Point::name() const
{
    return name_;
}

int Point::x() const
{
    return getX_;
}

int Point::y() const
{
    return getY_;
}

int Point::height() const
{
    return height_;
}

char Point::marker() const
{
    return marker_;
}
