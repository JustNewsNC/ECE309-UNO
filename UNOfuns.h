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
private:
    char type;
    int number;
public:
    char color;
    Card(char c = 'n', char t = 'n', int num = -1){ //n is for none, -1 is for none
        color = c;
        type = t;
        number = num; //-1 symbolizes that its not a number card (reverse, skip, draw, wild)
    }
    char cardtype() {return type;}
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
        return (color == 'W' || color == other->color || (type == other->type && number == other->number));
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
    std::vector<Card> dcards; //top of deck is just cards.back()
    DrawPile(){
        CreateDeck();
        Shuffle();
    }
    DrawPile(vector<Card> tmp) {
        dcards = tmp;
        numofcards = tmp.size();
        Shuffle();
    }
    bool isEmpty() { //returns whether deck is empty
        return numofcards <= 0;
    }
    void Deal(); //Deal starting cards to players

};

class PlayPile{ //Cards that have been played
public:
    std::vector<Card> pcards;
    int length;
    Card* topOfDeck() {return &pcards.back();}
    void PrintTop(){ //prints top card on play pile
        topOfDeck()->Print();
    }
    DrawPile* ReturnToDrawPile() { //return played cards back to the draw pile
        Card hold = *topOfDeck();
        pcards.pop_back(); //removes top card for returning pile
        vector<Card> temp = pcards;
        pcards.clear(); //empties playpile
        length = 0;
        pcards.push_back(hold); //puts most recently played card back into the pile
        DrawPile* newdraw = new DrawPile(temp); //takes the old playpile and converts to DrawPile to be shuffle and returned to deck
        return newdraw;
    }
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
        return &hcards[i]; //used to access card in hand
    }
    void remove(int index) { //removes card from hand vector
        Card hold;
        if(index != (int)hcards.size()-1) {
            hold = hcards[index];
            hcards[index] = hcards[(int)hcards.size()-1];
            hcards[(int)hcards.size()-1] = hold;
        }
        length--;
        hcards.pop_back();
    }
    void Draw(DrawPile* indrawstack) { //Draw a card from the draw pile
        hcards.push_back(indrawstack->dcards[indrawstack->dcards.size() - 1]); //top of stack is actually end of vector
        length++;
        indrawstack->dcards.pop_back();
        indrawstack->numofcards--;
    }
    void Print() { //View your current hand
        for(int i=0; i<(int)hcards.size(); i++) {
            std::cout << endl;
            std::cout << i+1 << ") ";
            hcards[i].Print();
        }
        cout << endl;
    }
};

struct Table{
    DrawPile* drawstack = new DrawPile();
    PlayPile* playstack = new PlayPile();
};

class Player {
public:
    string name;
    Hand currentCards;
    int numofcards;
    Player(string pname) {
        this->name = pname;
        numofcards = 0;
    }
    void draw(DrawPile* indrawstack) { //draws a card from drawpile and puts in players hand
        currentCards.Draw(indrawstack);
        numofcards++;
        cout << name << " drew." << endl;
    }
    virtual bool play(Table* table){ //base function to be overridden
        cout << "base" << endl;
        return false;
    }

    virtual char wildcolor() {return 'W';} //function to be overridden

    void FixWild(Table* table) { //changes wild from players color choice, back to wild
        if(table->playstack->topOfDeck()->cardtype() == 'C' || table->playstack->topOfDeck()->cardtype() == '4') {
            table->playstack->topOfDeck()->color = 'W';
        }
    }
};

class RealPlayer : public Player {
public:
    RealPlayer(string a):Player(a){};

    virtual bool play(Table* table) override { //GUI
        int input;
        Card *hold;
        cout << "Your Cards Are: ";
        currentCards.Print();
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
                    if (hold->playable(table->playstack->topOfDeck())) { //checks if chosen card is playable
                        FixWild(table);                                  //checks if played card is wild, and fixes it
                        table->playstack->pcards.push_back(*hold);
                        currentCards.remove(input-1);
                        numofcards--;
                        cout << name << " played "; table->playstack->topOfDeck()->Print(); cout << "." << endl;
                        return true;
                    }
                    cout << "Unplayable Card" << endl;
                } else cout << "Invalid Input" << endl;
            }
            else if(input == 2) { //draws card
                draw(table->drawstack);
                if(table->drawstack->isEmpty()) { //checks if drawpile is empty
                    table->drawstack = table->playstack->ReturnToDrawPile();
                }
                cout << "You Drew a "; currentCards.getCard(currentCards.length-1)->Print(); cout << endl;
                if(currentCards.getCard(currentCards.length-1)->playable(table->playstack->topOfDeck())) {
                    FixWild(table);
                    hold = currentCards.getCard(currentCards.length-1);
                    table->playstack->pcards.push_back(*hold);
                    currentCards.remove(currentCards.length-1);
                    cout << name << " played "; table->playstack->topOfDeck()->Print(); cout << "." << endl;
                    numofcards--;
                    return true;
                }
                return false;
            }
            else cout << "Invalid Input" << endl;
        }
    }

    virtual char wildcolor() override { //asks player for color choice for wild
        char hold;
        cout << "What Color would you like?" << endl;
        cin >> hold;
        return hold;
    }

};

class CompPlayer : public Player{
public:
    CompPlayer(int n): Player("COM ") {
        name += std::to_string(n);
    }
    virtual bool play(Table* table) override { //Automatically play/draw cards
        DrawPile* deck = table->drawstack;
        PlayPile* playpile = table->playstack;
        Card* currcard;

        for(int i=0; i<currentCards.length; i++) { //find first playable card in computers hand
            currcard = currentCards.getCard(i);
            if(currcard->playable(playpile->topOfDeck())) { //checks if card is playable
                FixWild(table);
                playpile->pcards.push_back(*currcard);
                currentCards.remove(i);
                cout << name << " played "; table->playstack->topOfDeck()->Print(); cout << "." << endl;
                numofcards--;
                return true;
            }
        }

        draw(deck); //if no playable cards, draw a card from the deck
        if(table->drawstack->isEmpty()) { //checks if drawpile is empty
            table->drawstack = table->playstack->ReturnToDrawPile();
        }
        currcard = currentCards.getCard(currentCards.length - 1);
        if(currcard->playable(playpile->topOfDeck())) { //if card is then playable, then play it. Otherwise return
            FixWild(table);
            playpile->pcards.push_back(*currcard);
            currentCards.remove(currentCards.length - 1);
            cout << name << " played "; table->playstack->topOfDeck()->Print(); cout << "." << endl;
            numofcards--;
            return true;
        }
        return false;
    }

    virtual char wildcolor() override { //chooses a wild color based on first colored card in computer hand
        for(int i=0; i<currentCards.length; i++) {
            if(currentCards.getCard(i)->color != 'W') return currentCards.getCard(i)->color;
        }
        int randnum = rand() % 4; //if no colors in hand, chose random color
        char colors[4] = {'R','B','G','Y'};
        return colors[randnum];
    }
};

void Action(Card* played, int &turnOrder, int &turnIndex, vector<Player*> &playerList, Table* table) {
    if(played->cardtype() == '2') { //if draw 2 was played
        turnIndex += turnOrder;     //increments to next player
        if(turnIndex >= (int)playerList.size()){
            turnIndex = 0;
        } else if(turnIndex < 0){
            turnIndex = (int)playerList.size() - 1;
        }
        for(int i=0;i<2;i++) playerList[turnIndex]->draw(table->drawstack); //draws two cards for that player
    }
    else if(played->cardtype() == 'R') { //if reverse is played
        turnOrder *= (-1);  //flip order
    }
    else if(played->cardtype() == 'S') { //if skip is played, increment turnIndex by 1
        turnIndex += turnOrder;
        if(turnIndex >= (int)playerList.size()){
            turnIndex = 0;
        } else if(turnIndex < 0){
            turnIndex = (int)playerList.size() - 1;
        }
    }
    else if(played->cardtype() == 'C') {        //calls wildcolor() for player to choose color for wild
        char hold = playerList[turnIndex]->wildcolor();
        table->playstack->topOfDeck()->color = hold;
    }
    else if(played->cardtype() == '4') {        //if wild draw 4, lets player choose color, then gives next player 4 cards from drawpile
        char hold = playerList[turnIndex]->wildcolor();
        table->playstack->topOfDeck()->color = hold;
        turnIndex += turnOrder;
        if(turnIndex >= (int)playerList.size()){
            turnIndex = 0;
        } else if(turnIndex < 0){
            turnIndex = (int)playerList.size() - 1;
        }
        for(int i=0;i<4;i++) playerList[turnIndex]->draw(table->drawstack);
    }

}
