#include "orienteeringmap.hh"
#include <iostream>

OrienteeringMap::OrienteeringMap()
{
}

OrienteeringMap::~OrienteeringMap()
{
}

void OrienteeringMap::set_map_size(int width, int height)
{
    this->x = width;
    this->y = height;
}

void OrienteeringMap::add_point(std::string name, int x, int y, int height, char marker)
{
    return;
}

bool OrienteeringMap::connect_route(std::string from, std::string to, std::string route_name)
{
    return false;
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


