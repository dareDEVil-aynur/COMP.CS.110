#include "player.hh"
#include <string>
#include <iostream>

using namespace std;

Player::Player(const string name):
    name_(name)
{

}

string Player::get_name() {

    return name_;
}

void Player::add_points(int pts) {

    if (points_ + pts > 50) {
        cout << get_name() << " gets penalty points!" << endl;
        points_ = 25;
    } else {
        points_ += pts;
    }
}

bool Player::has_won() {

    if (points_ == 50) {
        return true;
    } else {
        return false;
    }
}

int Player::get_points() {

    return points_;
}
