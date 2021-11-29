

#ifndef ECE309_UNO_UNOFUNS_H
#define ECE309_UNO_UNOFUNS_H

#endif //ECE309_UNO_UNOFUNS_H
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

using std::string;
int randomnum (int i) { return std::rand()%i;}

class Card {
private:
    char color;
    char type;
    int number;
public:
    Card(char c = 'n', char t = 'n', int num = -1){ //n is for none, -1 is for none
        color = c;
        type = t;
        number = num; //-1 symbolizes that its not a number card (reverse, skip, draw, wild)
    }
    Card(const Card &other) { //copy constructor
        color = other.color;
        type = other.type;
        number = other.number;
    }
    Card& operator= (const Card &other) { //assignment operator
        color = other.color;
        type = other.type;
        number = other.number;
        return *this;
    }
    ~Card(){} //destructor

    void Print() { //prints card information
        std::cout << color << type << number << std::endl;
    }
};

class DrawPile{ //Cards to draw/deal from
private:
    char colors[5] = {'R', 'B', 'G', 'Y', 'W'}; //RED, BLUE, GREEN, YELLOW, WILD
    char types[6] = {'R','S','2', 'C', '4', 'N'}; //REVERSE, SKIP, DRAW 2, CHOOSE, DRAW 4, NUMBER
public:
    int numofcards = 0;
    std::vector<Card> cards; //top of deck is just cards.begin()
    DrawPile(){
        CreateDeck();
        Shuffle();
    }
    void CreateDeck() {
        for(int i=0; i<4; i++) {
            cards.push_back(Card(colors[i],'N', 0));
            numofcards++;
            for(int j=1;j<10;j++) {
                cards.push_back(Card(colors[i],'N', j));
                cards.push_back(Card(colors[i],'N', j));
                numofcards+=2;
            }
        }
        for(int i=0; i<4; i++) {
            for(int j=0; j<3; j++) {
                cards.push_back(Card(colors[i],types[j], -1));
                cards.push_back(Card(colors[i],types[j], -1));
                numofcards+=2;
            }
        }
        for(int i=0; i<2; i++) {
            for(int j=0; j<4; j++) {
                cards.push_back(Card('W',types[3+i], -1));
                numofcards++;
            }
        }
    }
    void Shuffle() {
        std::srand ( unsigned ( std::time(0) ) );
        std::random_shuffle(cards.begin(), cards.end(), randomnum);
    }
    void Deal(){} //Deal starting cards to players
};

class PlayPile{ //Cards that have been played
private:
    std::vector<Card> cards;
public:
    int length;
    Card* topOfDeck;
    PlayPile(){
        length = 0;
        topOfDeck = nullptr;
    }
    void PrintTop(){ //prints top card on play pile
        cards.begin()->Print();
    }
    void ReturnToDrawPile(){} //return played cards back to the draw pile
};

//player's cards
class Hand{
private:
    std::vector<Card> cards;
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
        this->name = name;
        //numofcards = 0;               //remove comment when variables initialized
        //currentcards = new Hand();
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
    CompPlayer(int n): Player("COM ") {
        name += n;
    }
    virtual void play(){}; //Automatically play/dray cards
};

