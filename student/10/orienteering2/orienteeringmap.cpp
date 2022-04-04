/*
 *
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures          #
# Project3: Suunnistus / Orienteering                                       #
# File: orienteeringmap.cpp                                                         #
# Description: Module that parses the input file into an OrienteeringMap    #
#        object.                                                            #
# Notes: * This is a part of an exercise program.                           #
#        * Student's don't touch this file.                                 #
#        * Understanding how the module works isn't necessary to complete   #
#          this exercise.                                                   #
#############################################################################
*/

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
void OrienteeringMap::print_routes() const
{
    cout << "Routes:" << endl;

    for(const auto& routes : route_)
    {
        cout << " - " << routes.first
                  << endl;
    }

}
// Käyttöliittymän points -komennolle
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


