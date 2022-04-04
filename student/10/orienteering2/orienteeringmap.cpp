#include "orienteeringmap.hh"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "point.hh"

OrienteeringMap::OrienteeringMap()
{
}

OrienteeringMap::~OrienteeringMap()
{

}

void OrienteeringMap::set_map_size(int width, int height)
{
    this->x_ = width;
    this->y_ = height;
}

void OrienteeringMap::add_point(std::string name, int x, int y, int height, char marker)
{
    Point* point = new Point({name, x, y, height, marker});
    points_.insert({name, point});

}

bool OrienteeringMap::connect_route(std::string from, std::string to, std::string route_name)
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

void OrienteeringMap::print_map() const
{
    return;
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


