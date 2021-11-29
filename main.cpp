//
//
//
#include <iostream>
#include "UNOfuns.h"
#include <vector>

using namespace std;
vector<Player> playerList;

//fills a vector with the specified amount of bots
void createPlayers(int amount){
    int i = 0;
    while(i <= amount){
        playerList.push_back(new CompPlayer(i));
        i++;
    }
}

//Game setup function when a player is present
void GameStartWithPlayer(){
    string name;
    char input;
    cout << "Welcome! What is your name?" << endl;
    cin >> name;
    playerList.push_back(new RealPlayer(name));
    cout << "Are you readY to play, " << playerList.front().name << "? (Y/N)" << endl;
    cin >> input;

    int playerCount = 0;
    if(toupper(input == 'Y')){
        cout << "How many enemies would you like to play against? (1-3)" << endl;
        cin >> playerCount;
        createPlayers(playerCount);
    } else {
        main(); //why are you calling main here?
    }
}

//setups a game for spectators
void GameStartNoPlayer(){
    int input = 0;
    cout << "How many computers would you like to see play?" << endl;
    cin >> input;
    createPlayers(playerCount); //need to initialize playerCount
    return;
}


int main() {
    int turnCount = 1;
    char input;
    bool winner;
    cout << "Are you a player or spectator? (P/S)" << endl;
    cin >> input;
    if(input == 'P'){
        GameStartWithPlayer();
    }
    else {
        GameStartNoPlayer();
    }
    DrawPile* draw = new DrawPile();
    draw->Deal();
    PlayPile* play = new PlayPile();
    int playerIndex = 0;
    Player* currentPlayer = nullptr;
    
    while(!winner){
        cout << "Turn " << turnCount << ". -------------" << endl;
        cout << "The card on top is: " << play->PrintTop() << endl;
        playerIndex = currentTurn % playerList.size; //Finds the remainder on the turn count to shortcut keeping track of the player list
        currentPlayer = playerList[playerIndex];
        cout << "It is " << currentPlayer->name << "'s turn" << endl;
        currentPlayer->play(); //play function differs between AI and humans
        cout << currentPlayer->name << " played " << play->PrintTop() << endl;
        if(currentPlayer->currentCards.length == 0){
            cout << currentPlayer->name << " has won!" << endl;
            winner = true;
        }
    }
    return 0;
}



