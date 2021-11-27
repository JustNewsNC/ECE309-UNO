

#ifndef ECE309_UNO_UNOFUNS_H
#define ECE309_UNO_UNOFUNS_H

#endif //ECE309_UNO_UNOFUNS_H
#include <string>


using std::string;


class Card {
private:
    char color;
    char type;
    int number;
public:
    Card(char c, char t, int num;){
        color = c;
        type = t;
        number = num;
    }
    string Print(){} //returns a string describing the card
};

class DrawPile{ //Cards to draw/deal from
private:
    char[4] colors = {'R', 'B', 'G', 'Y', 'W'}
    char[6] types = {'R', 'S', 'C', '2', '4', 'N'}
    vector<Card> cards;
public:
    Card* topOfDeck;
    DrawPile(){}
    void Deal(){} //Deal starting cards to players
    void Shuffle(){}
};

class PlayPile{ //Cards that have been played
private:
    vector<Card> cards;
public:
    int length;
    Card* topOfDeck;
    PlayPile(){
        length = 0;
        topOfDeck = nullptr;
    }
    string PrintTop(){
        return topOfDeck->Print();
    }
    void ReturnToDrawPile(){} //return played cards back to the draw pile
};

//player's cards
class Hand{
private:
    vector<Card> cards;
public:
    int length;
    Hand(){
        length = 0;
    }
    void Play(){} //Play a card to the play pile
    void Draw(){} //Draw a card from the draw pile
    void Print(){} //View your current hand
};

class Player{
public:
    string name;
    Hand currentCards;
    Player(string name) {
        this.name = name;
        numofcards = 0;
        currentcards = new Hand();
    }
    virtual void play(){}
    
};

class RealPlayer : public Player{
public:
    RealPlayer(string a):Player(a){};
    virtual void play(){} //GUI
};

class CompPlayer : public Player{
public:
    CompPlayer(int n){
        name = "COM " + n;
    }
    virtual void play(){}; //Automatically play/dray cards
};

