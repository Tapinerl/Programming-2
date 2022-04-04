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
    int Getx_;
    int Gety_;
    int height_;
    char marker_;


};

#endif // POINT_HH
