#include "player.hh"
#include <iostream>

Player::Player(std::string const &pelaaja):
    name_(pelaaja), points_(0)

{

}

void Player::add_points(int points)
{
    points_ += points;
    if(points_ > WINNING_POINTS)
    {
        points_ = PENALTY_POINTS;
    }
}

bool Player::has_won()
{
    return points_ == WINNING_POINTS;
}

int Player::get_points()
{
    return points_;
}

std::string Player::get_name()
{
    return name_;
}


