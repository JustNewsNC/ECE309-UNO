//
// You can change anything that needs fixing, i didn't have much time to work on it
//

#ifndef ECE309_UNO_UNOFUNS_H
#define ECE309_UNO_UNOFUNS_H

#endif //ECE309_UNO_UNOFUNS_H
#include <string>

using std::string;

class Card {
private:
    char color;
    int number;
};

void shufflecards();

class Player{
public:
    string name;
    int numofcards;

    Player(string a) {
        name = a;
        numofcards = 0; //start with zero, so when cards are dealt the number is incremented to 7 that way
    }

    void display(); //can be implemented in base class
    virtual void placecard() = 0; //different for both computer and real player
    virtual void pickcard() = 0; //
};

class RealPlayer : public Player{
public:
    RealPlayer(string a):Player(a){};
    virtual void placecard();
    virtual void pickcard();
};

class CompPlayer : public Player{
public:
    CompPlayer(string a):Player(a){};
    virtual void placecard();
    virtual void pickcard();
};