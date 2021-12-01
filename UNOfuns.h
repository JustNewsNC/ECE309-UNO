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

using std::string;
int randomnum (int i) { return std::rand()%i;}

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
        else std::cout << "Draw 2";
    }
};

class DrawPile{ //Cards to draw/deal from
private:
    char colors[5] = {'R', 'B', 'G', 'Y', 'W'}; //RED, BLUE, GREEN, YELLOW, WILD
    char types[6] = {'R','S','2', 'C', '4', 'N'}; //REVERSE, SKIP, DRAW 2, CHOOSE, DRAW 4, NUMBER
public:
    int numofcards = 0;
    std::vector<Card> dcards; //top of deck is just cards.end()
    DrawPile(){
        CreateDeck();
        Shuffle();
    }
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
    void Play(); //Play a card to the play pile
    void Draw() { //Draw a card from the draw pile
        hcards.push_back(drawstack->dcards[drawstack->dcards.size() - 1]); //top of stack is actually end of vector
        length++;
        drawstack->dcards.pop_back();
    }
    void Print() { //View your current hand
        for(int i=0; i<(int)hcards.size(); i++) {
            std::cout << i+1 << ") ";
            hcards[i].Print();
            std::cout << ", ";
        }
    }
};

class Player{
public:
    string name;
    int numofcards;
    Hand currentCards;
    Player(string pname) {
        this->name = pname;
        numofcards = 0;
    }
    virtual void play() {std::cout << "Did base" << std::endl;} //testing which function it calls (remove later)

};

class RealPlayer : public Player{
public:
    RealPlayer(string a):Player(a){};
    virtual void play() { //GUI
        int input;
        Card *hold;
        cout << "You have " << numofcards << " Remaining!" << endl;
        while (1) {
            cout << "Your Cards Are: ";
            currentCards.Print();
            cout << endl;
            cout << "Which Card do you Wish to Play? (please enter card number)" << endl;
            cin >> input;
            if (input >= 1 && input < currentCards.length + 1) {
                hold = currentCards.getCard(input - 1);
                if (hold->color == playstack->topOfDeck->color ||
                    (hold->type == playstack->topOfDeck->type && hold->number == playstack->topOfDeck->number)) {
                    playstack->pcards.push_back(*hold);
                    currentCards.remove(input);
                    return;
                }
                cout << "Unplayable Card" << endl;
            } else cout << "Invalid Input" << endl;
            return;
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