#ifndef ECE309_UNO_UNOFUNS_H
#define ECE309_UNO_UNOFUNS_H

#endif //ECE309_UNO_UNOFUNS_H
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;
int randomnum (int i) { return rand()%i;}


class Card {
public:             //currently public for convenience will fix later
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

    bool playable(Card* other) {
        return (color == other->color || (type == other->type && number == other->number));
    }

    void Print() { //prints card information
        if(color == 'R') std::cout << "Red ";
        else if(color == 'B') std::cout << "Blue ";
        else if(color == 'G') std::cout << "Green ";
        else if(color == 'Y') std::cout << "Yellow ";
        else if(color == 'W') {
            std::cout << "Wild ";
            if(type == 4) std::cout << "Draw 4";
        }
        if(type == 'N') std::cout << number;
        else if (type == 'R') std::cout << "Reverse";
        else if (type == 'S') std::cout << "Skip";
        else if (type == '2') std::cout << "Draw 2";
    }
};

class DrawPile{ //Cards to draw/deal from
private:
    char colors[5] = {'R', 'B', 'G', 'Y', 'W'}; //RED, BLUE, GREEN, YELLOW, WILD
    char types[6] = {'R','S','2', 'C', '4', 'N'}; //REVERSE, SKIP, DRAW 2, CHOOSE, DRAW 4, NUMBER
    void CreateDeck() {
        for(int i=0; i<4; i++) {
            dcards.push_back(Card(colors[i],'N', 0));
            numofcards++;
            for(int j=1;j<10;j++) {
                dcards.push_back(Card(colors[i],'N', j));
                dcards.push_back(Card(colors[i],'N', j));
                numofcards+=2;
            }
        }
        for(int i=0; i<4; i++) {
            for(int j=0; j<3; j++) {
                dcards.push_back(Card(colors[i],types[j], -1));
                dcards.push_back(Card(colors[i],types[j], -1));
                numofcards+=2;
            }
        }
        for(int i=0; i<2; i++) {
            for(int j=0; j<4; j++) {
                dcards.push_back(Card('W',types[3+i], -1));
                numofcards++;
            }
        }
    }
    void Shuffle() {
        std::srand ( unsigned ( std::time(0) ) );
        std::random_shuffle(dcards.begin(), dcards.end(), randomnum);
    }
public:
    int numofcards = 0;
    std::vector<Card> dcards; //top of deck is just cards.end()
    DrawPile(){
        CreateDeck();
        Shuffle();
    }
    void Deal(); //Deal starting cards to players
};

class PlayPile{ //Cards that have been played
public:
    std::vector<Card> pcards;
    int length;
    Card* topOfDeck;
    PlayPile(){
        length = 0;
        topOfDeck = nullptr;
    }
    void PrintTop(){ //prints top card on play pile
        pcards.end()->Print();
    }
    void ReturnToDrawPile(){} //return played cards back to the draw pile
};

//player's cards
class Hand{
private:
    std::vector<Card> hcards;
public:
    int length;
    Hand(){
        length = 0;
    }
    Card* getCard(int i) {
        return &hcards[i];
    }
    void remove(int index) {
        Card hold;
        if(index != (int)hcards.size()-1) {
            hold = hcards[index];
            hcards[index] = hcards[(int)hcards.size()-1];
            hcards[(int)hcards.size()-1] = hold;
        }
        hcards.pop_back();
    }
    void Draw(DrawPile* indrawstack) { //Draw a card from the draw pile
        hcards.push_back(indrawstack->dcards[indrawstack->dcards.size() - 1]); //top of stack is actually end of vector
        length++;
        indrawstack->dcards.pop_back();
    }
    void Print() { //View your current hand
        for(int i=0; i<(int)hcards.size(); i++) {
            std::cout << i+1 << ") ";
            hcards[i].Print();
            std::cout << ", ";
        }
    }
    void Play(); //Play a card to the play pile
};

DrawPile* drawstack = new DrawPile();

class Player{
public:
    string name;
    Hand currentCards;
    int numofcards;
    Player(string pname) {
        this->name = pname;
        numofcards = 0;
    }
    virtual void play() {std::cout << "Did base" << std::endl;} //testing which function it calls (remove later)
    virtual void draw(DrawPile* indrawstack) {
        currentCards.Draw(indrawstack);
        numofcards++;
    }
};

class RealPlayer : public Player{
public:
    RealPlayer(string a):Player(a){};

    virtual void play(PlayPile* inplaystack) { //GUI
        int input;
        Card *hold;
        cout << "You have " << numofcards << " Remaining!" << endl;
        cout << "Your Cards Are: ";
        currentCards.Print(); cout << endl;
        cout << "Top Card on Pile is:"; inplaystack->PrintTop(); cout << endl;
        while (1) {
            cout << endl << "Do you wish to Play a Card or Draw a card?" << endl << "1) Play" << endl << "2) Draw" << endl;
            cin >> input;
            if(input == 1) {
                cout << "Your Cards Are: ";
                currentCards.Print();
                cout << endl << "Which Card do you Wish to Play? (please enter card number)" << endl;
                cin >> input;
                if (input >= 1 && input < currentCards.length + 1) {
                    hold = currentCards.getCard(input - 1);
                    if (hold->playable(inplaystack->topOfDeck)) {
                        inplaystack->pcards.push_back(*hold);
                        currentCards.remove(input);
                        return;
                    }
                    cout << "Unplayable Card" << endl;
                } else cout << "Invalid Input" << endl;
            }
            else if(input == 2) {
                draw(drawstack);
                cout << "You Drew a "; currentCards.getCard(currentCards.length-1)->Print(); cout << endl;
                if(currentCards.getCard(currentCards.length-1) )
                return;
            }
            else cout << "Invalid Input" << endl;
        }
    }
};

class CompPlayer : public Player{
public:
    CompPlayer(int n): Player("COM ") {
        name += std::to_string(n);
    }
    virtual void play() {}; //Automatically play/dray cards
};