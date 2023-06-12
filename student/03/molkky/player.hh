#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player
{
public:
    Player(const string name);

    string get_name();

    void add_points(int pts);

    bool has_won();

    int get_points();

private:

    string name_;
    int points_ = 0;
};

#endif // PLAYER_HH
