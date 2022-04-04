#include "point.hh"


Point::Point(std::string name, int x, int y, int height, char marker) :
             name_(name), Getx_(x), Gety_(y), height_(height), marker_(marker)
{}

std::string Point::name() const
{
    return name_;
}

int Point::x() const
{
    return Getx_;
}

int Point::y() const
{
    return Gety_;
}

int Point::height() const
{
    return height_;
}

char Point::marker() const
{
    return marker_;
}
