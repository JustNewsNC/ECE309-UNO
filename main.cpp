//
//
//
#include <iostream>
#include "UNOfuns.h"
#include <vector>

vector<Player> PLAYERLIST;

int main() {
    int turnCount = 1;
    char input;
    bool winner;
    cout << "Are you a player or spectator? (P/S)" << endl;
    cin >> input;
    if(input == 'P'){
        GameStartWithPlayer()
    } else {
        GameStartNoPlayer()
    }
    DrawPile* draw = new DrawPile()
    DrawPile->deal();
    PlayPile* play = new PlayPile();
    int playerIndex = 0;
    Player* currentPlayer = nullptr;
    
    While(!winner){
        cout << "Turn " << turnCount << ". -------------" << endl;
        cout << "The card on top is: " << play->PrintTop() << endl;
        playerIndex = currentTurn % PLAYERLIST.size; //Finds the remainder on the turn count to shortcut keeping track of the player list
        currentPlayer = PLAYERLIST[playerIndex]
        cout << "It is " << currentPlayer->name << "'s turn" << endl;
        currentPlayer->play(); //play function differs between AI and humans
        cout << currentPlayer->name << " played " << play->PrintTop() << endl;
        if(currentPlayer->currentCards.length == 0){
            cout << playerList->name << " has won!" << endl;
            winner = true;
        }
        
        
    }
    return 0;
}

//Game setup function when a player is present
void GameStartWithPlayer(){
    string name;
    char input;
    cout << "Welcome! What is your name?" << endl;
    cin >> name;
    playerList.pushBack(new RealPlayer(name));
    cout << "Are you readt to play, " << PLAYERLIST.front()->name << "? (Y/N)" << endl;
    cin >> input;
    
    int playerCount = 0;
    if(toupper(input == 'Y')){
        cout << "How many enemies would you like to play against? (1-3)" << endl;
        cin >> playerCount;
        createPlayers(playerCount);
    } else {
        main();
    }
}

//setups a game for spectators
void GameStartNoPlayer(){
    int input = 0;
    cout << "How many computers would you like to see play?" << endl;
    cin >> input;
    createPlayers(playerCount);
    return;
}

//fills a vector with the specified amount of bots
void createPlayers(int amount){
    int i = 0;
    while(i <= amount){
        playerList.pushBack(new CompPlayer(i))
    }
    return;
}

