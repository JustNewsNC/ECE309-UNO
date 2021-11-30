//
//
//
#include <iostream>
#include "UNOfuns.h"
#include <vector>

using namespace std;
vector<Player> playerList;
DrawPile* drawstack = new DrawPile();
PlayPile* playstack = new PlayPile();

//fills a vector with the specified amount of bots
void createPlayers(int amount){
    int i = 1;
    while(i < amount + 1){
        playerList.push_back(CompPlayer(i));
        i++;
    }
}

//Game setup function when a player is present
void GameStartWithPlayer(){
    string name;
    char input;
    cout << "Welcome! What is your name?" << endl;
    cin >> name;
    playerList.push_back(RealPlayer(name));
    while(1) {
        cout << "Are you Ready to play, " << playerList.front().name << "? (Y/N)" << endl;
        cin >> input;
        int playerCount = 0;
        if (input == 'Y' || input == 'y') {
            while(playerCount < 1 || playerCount > 3) {
                cout << "How many enemies would you like to play against? (1-3)" << endl;
                cin >> playerCount;
                if(playerCount < 1 || playerCount > 3) cout << "Please Enter Valid Number" << endl;
                else {
                    createPlayers(playerCount);
                    return;
                }
            }
        }
        else if(input == 'N' || input == 'n') {
            cout << "Exiting Game" << endl;
            abort();
        }
        else {
            cout << "Please enter either Y or N" << endl;
        }
    }
}

//setups a game for spectators
void GameStartNoPlayer(){
    int playerCount = 0;
    cout << "How many computers would you like to see play?" << endl;
    cin >> playerCount;
    createPlayers(playerCount); //need to initialize playerCount
}

void Hand::Draw() {
    hcards.push_back(drawstack->dcards[drawstack->dcards.size()-1]); //top of stack is actually end of vector
    length++;
    drawstack->dcards.pop_back();
}

void DrawPile::Deal() {
    for(int i=0; i<7; i++) {
        for(int j=0; j<(int)playerList.size(); j++) {
            playerList[j].currentCards.Draw();
            playerList[j].numofcards++;
            numofcards--;
        }
    }
}

void RealPlayer::play() {
    int input;
    Card* hold;
    cout << "You have " << numofcards << " Remaining!" << endl;
    while(1) {
        cout << "Your Cards Are: ";
        currentCards.Print();
        cout << endl;
        cout << "Which Card do you Wish to Play? (please enter card number)" << endl;
        cin >> input;
        if(input >= 1 && input < currentCards.length + 1) {
            hold = currentCards.getCard(input-1);
            if(hold->color == playstack->topOfDeck->color || (hold->type == playstack->topOfDeck->type && hold->number == playstack->topOfDeck->number)) {
                playstack->pcards.push_back(*hold);
                currentCards.remove(input);
                return;
            }
            cout << "Unplayable Card" << endl;
        }
        else cout << "Invalid Input" << endl;
        return;
    }
}

int main() {
    char input;
    bool winner = false;
    cout << "Are you a player or spectator? (P/S)" << endl;
    cin >> input;
    if(input == 'P' || input == 'p'){
        GameStartWithPlayer();
    }
    else {
        GameStartNoPlayer();
    }
    drawstack->Deal();
    playstack->pcards.push_back(drawstack->dcards[drawstack->numofcards-1]);
    playstack->length++;
    drawstack->dcards.pop_back();
    drawstack->numofcards--;

    for(int i=0; i<(int)playerList.size(); i++) { //prints all players card (used to test shuffle, deal, and draw)
        cout << playerList[i].name << ": ";
        playerList[i].currentCards.Print();
        cout << endl;
        playerList[i].play(); // I can't get the compiler to call the RealPlayer.play()
    }


    /*int playerIndex = 0;
    Player* currentPlayer = nullptr;
    
    while(!winner){
        cout << "The card on top is: "; playstack->PrintTop(); cout << endl;
        currentPlayer = &playerList[playerIndex];
        cout << "It is " << currentPlayer->name << "'s turn" << endl;
        //currentPlayer->play(); //play function differs between AI and humans
        cout << currentPlayer->name << " played "; playstack->PrintTop(); cout << endl;
        if(currentPlayer->currentCards.length == 0){
            cout << currentPlayer->name << " has won!" << endl;
            winner = true;
        }
        if(playerIndex < (int)playerList.size()-1) playerIndex++;
        else playerIndex = 0;
    }*/
    return 0;
}



