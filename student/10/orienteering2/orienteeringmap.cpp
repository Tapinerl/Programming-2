
/*  COMP.CS.110 Project 3: Orienteering
 *
 * orienteeringmap.cpp
 *
 * Ohjelma lukee syötetidostosta tietoja joihin kuuluu
 * kartan koko, rasti kartalla (ja sen koordinaatit)
 * ja polut.
 * Eli ohjelmalla on erilaisia reittejä joihin kuuluu
 * erilaisia polkuja.
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Elias Nikkinen
 * Opiskelijanumero: 50497168
 * Käyttäjätunnus: shelni
 * E-Mail: elias.nikkinen@tuni.fi
 *
 * */
#include "orienteeringmap.hh"
#include <iostream>
using namespace std;


OrienteeringMap::OrienteeringMap()
{

}

OrienteeringMap::~OrienteeringMap()
{
    // Muistin vapautus
    for( map<string, Point*>::iterator
         iter = points_.begin();
         iter != points_.end();
         ++iter )
    {
        delete iter->second;
    }
}
// Asettaa kartan koon
void OrienteeringMap::set_map_size(int width, int height)
{
    this->x_ = width;
    this->y_ = height;
}
// tekee uuden rastin saaduilla tiedoilla ja lisää ne karttaan
void OrienteeringMap::add_point(string name, int x, int y, int height, char marker)
{
    Point* point = new Point({name, x, y, height, marker});
    points_.insert({name, point});

}

// Puskee reittien nimet ja niiden polut tietorakenteeseen
bool OrienteeringMap::connect_route(string from, string to, string route_name)
{
    if(points_.find(from) == points_.end() ||
            points_.find(to) == points_.end())
    {
        return false;
    }
    else
    {
        if(route_.find(route_name) == route_.end())
        {
            route_.insert({route_name,{from, to}});
        }
        else
        {
            route_.at(route_name).push_back(to);
        }
        return true;
    }
}

// Käyttöliittymän MAP -komennolle.
// Tulostaa matriisin näkyisen kartan rasteille
void OrienteeringMap::print_map() const
{
    cout << " ";
    for(int x = 1; x <= x_; x++)
    {
        cout <<  setw(3) << x;
    }
    cout << "\n";

    for(int y = 1; y <= y_; y++)
    {
        cout << setw(2) << y << "  ";
        for(int x = 1; x <= x_; x++)
        {
            bool find_pt = false;

            for(auto const& point : points_)
            {
                if(x == point.second->x()
                        && y == point.second->y())
                {
                    find_pt = true;
                    cout << point.second->marker();
                }
            }
            if(find_pt == false)
            {
                cout << ".";
            }
            if(x < x_)
            {
                cout << "  ";
            }
            if(x == x_)
            {
                cout << "\n";
            }
        }
    }
}
// Käyttöliittymän ROUTES -komennolle
// Tulostaa reittien nimet
void OrienteeringMap::print_routes() const
{
    cout << "Routes:" << endl;

    for(const auto& routes : route_)
    {
        cout << " - " << routes.first
                  << endl;
    }

}
// Käyttöliittymän POINTS -komennolle
// Tulostaa rastit
void OrienteeringMap::print_points() const
{
    cout << "Points:" << endl;

    for(const auto& pt : points_)
    {
        cout << " - " << pt.first << " : "
                  << pt.second->marker() << endl;
    }

}
// käyttöliittymän ROUTE <input> -komennolle
// Tulostaa kysytyn reitin polun
void OrienteeringMap::print_route(const string &name) const
{
    if(route_.find(name) == route_.end())
    {
        cout << "Error: Route named " << name
                  <<  " can't be found" << endl;
    }
    else
    {
        cout << route_.at(name).at(0) << endl;
        for(unsigned int i = 1; i < route_.at(name).size(); i++)
        {
            cout << " -> " << route_.at(name).at(i) << endl;
        }
    }
}

void OrienteeringMap::route_length(const std::string &name) const
{
    if(route_.find(name) == route_.end())
    {
        cout << "Error: Route named " << name
                  <<  " can't be found" << endl;
    }
    return;
}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    if(route_.find(point_name) == route_.end())
    {
        cout << "Error: Route named " << point_name
                  <<  " can't be found" << endl;
    }
    return;
}


