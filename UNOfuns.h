

#ifndef ECE309_UNO_UNOFUNS_H
#define ECE309_UNO_UNOFUNS_H

#endif //ECE309_UNO_UNOFUNS_H
#include <string>
#include <vector>


using std::string;



class Card {
private:
    char color;
    char type;
    int number;
public:
    Card(char c, char t, int num){
        color = c;
        type = t;
        number = num; //-1 symbolizes that its not a number card (reverse, skip, draw, wild)
    }
    string Print(); //returns a string describing the card
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
    void Shuffle(){}
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
    string PrintTop(){
        return topOfDeck->Print();
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

