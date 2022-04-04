#include "orienteeringmap.hh"
#include <iostream>
#include "point.hh"

using namespace std;

OrienteeringMap::OrienteeringMap()
{
}

OrienteeringMap::~OrienteeringMap()
{

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
    if(points_.find(from) == points_.end() || points_.find(to) == points_.end())
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
                if(x == point.second->x() && y == point.second->y())
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

void OrienteeringMap::print_routes() const
{
    return;
}

void OrienteeringMap::print_points() const
{
    return;
}

void OrienteeringMap::print_route(const std::string &name) const
{
    return;
}

void OrienteeringMap::route_length(const std::string &name) const
{
    return;
}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    return;
}


