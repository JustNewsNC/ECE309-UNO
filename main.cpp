//
//
//
#include <iostream>
#include "UNOfuns.h"
#include <vector>


using namespace std;
Table PlayTable = Table();
vector<Player*> playerList;

void NewPlayer(int playerCount){
    int currentPlayerID = 1;
    int maxPlayers = 4;
    string name;
    RealPlayer* temp;
    while(currentPlayerID <= (playerCount+1)){
        cout << "Please enter the name of Player " << currentPlayerID << "." << endl;
        cin >> name;
        temp = new RealPlayer(name);
        playerList.push_back(temp);
        currentPlayerID++;
    }
}

//fills a vector with the specified amount of bots
void NewBots(int botCount){
    int i = 1;
    while(i < botCount + 1){
        CompPlayer* temp = new CompPlayer(i);
        playerList.push_back(temp);
        i++;
    }
}

//Game setup function when a player is present
void GameStartWithPlayer(){
    string name;
    char input;
    int playerCount = 1;
    int botCount = 0;
    int maxPlayers = 4;
    cout << "Would you like to play against other players? (Y/N)" << endl;
    cin >> input;
    if(input == 'Y' || input == 'y'){
        cout << "How many other players are there? (1-3)" << endl;
        cin >> playerCount;
        NewPlayer(playerCount++);
        
    } else if(input == 'N' || input == 'n') {
        NewPlayer(playerCount);
    }
    while(1) {
        cout << "Are you Ready to play, " << playerList.front()->name << "? (Y/N)" << endl;
        cin >> input;
        int maxBots = maxPlayers - playerCount;
        int minBots = 1;
        if (input == 'Y' || input == 'y') {
            while(botCount < 1 || botCount > maxBots) {
                if(playerCount >= 2){
                    minBots = 0;
                } else {
                    minBots = 1;
                }
                cout << "How many bots would you like to play against? (" << minBots << "-" <<  maxBots << ")" << endl;
                cin >> botCount;
                if(botCount < minBots || botCount > maxBots){
                    cout << "Please Enter Valid Number" << endl;
                } else {
                    NewBots(botCount);
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
    while(1) {
        cout << "How many computers would you like to see play? (2 to 4)" << endl;
        cin >> playerCount;
        if(playerCount >= 2 && playerCount <= 4) { //Game works best with between 2 to 4 players.
            NewBots(playerCount);
            return;
        }
        cout << "Please Enter Valid Number." << endl;
    }
}


void DrawPile::Deal() {
    for(int i=0; i<7; i++) { //deals out 7 cards to each player
        for(int j=0; j<(int)playerList.size(); j++) {
            playerList[j]->currentCards.Draw(PlayTable.drawstack);
            playerList[j]->numofcards++;
            numofcards--;
        }
    }
}



int main() {
    char input;
    bool winner = false;
    int maxCount = 4;
    cout << "Are you a player or spectator? (P/S)" << endl;
    while(1) {
        cin >> input;
        if(input == 'P' || input == 'p'){
            GameStartWithPlayer();
            break;
        }
        else if (input == 'S' || input == 's') {
            GameStartNoPlayer();
            break;
        }
        cout << "Please Enter Valid Mode" << endl;
    }
    PlayTable.drawstack->Deal();
    PlayTable.playstack->pcards.push_back(PlayTable.drawstack->dcards[PlayTable.drawstack->numofcards-1]);
    PlayTable.playstack->length++;
    PlayTable.drawstack->dcards.pop_back();
    PlayTable.drawstack->numofcards--;

    /*cout << "Debug Mode: Y/N" << endl;
    cin >> input;
    if(input == 'Y' || input == 'p'){
        for(int i=0; i<(int)playerList.size(); i++) { //prints all players card (used to test shuffle, deal, and draw)
            cout << playerList[i]->name << ": ";
            playerList[i]->currentCards.Print();
            cout << endl;
            playerList[i]->play(&PlayTable);
        }

        RealPlayer Sam = RealPlayer("Sam");
        Player* ptr = &Sam;
        for(int i=0; i<60; i++) ptr->draw(PlayTable.drawstack);
        int given = 1;
        while(given != 0) {
            cin >> given;
            ptr->play(&PlayTable);
        }
        cout << "The current card on top is ";
        PlayTable.playstack->PrintTop();
        cout << ". " << endl;

    } */  //Can Probably Be Deleted Soon
    
    int turnIndex = 0; //turn order
    int turnCount = 0; //turn count
    int turnOrder = 1;
    bool cardplayed = false;
    Player* currentPlayer = playerList[turnIndex];
    while(!winner){
        currentPlayer = playerList[turnIndex];
        cout << "Turn: " << turnCount << " -----------------" << endl;
        cout << "It is " << currentPlayer->name << "'s turn" << endl;
        cout << "The current card on top is ";
        PlayTable.playstack->PrintTop();
        cout << ". " << endl;
        
        cardplayed = currentPlayer->play(&PlayTable);
        if(cardplayed) { //checks if card is played
            Action(PlayTable.playstack->topOfDeck(), turnOrder, turnIndex, playerList, &PlayTable);
        }

        if(currentPlayer->numofcards == 1){ //shows if a player has UNO
            cout << currentPlayer->name << " has UNO!" << endl;
        } else if(currentPlayer->numofcards == 0) { //declares a winner
            cout << currentPlayer->name << " has won!" << endl;
            winner = true;
        }
        
        turnIndex += turnOrder; //increments player in vector
        if(turnIndex >= (int)playerList.size()){ //loops around back to zero
            turnIndex = 0;
        } else if(turnIndex < 0){ //loops around to end of list in case of reverse order
            turnIndex = (int)playerList.size() - 1;
        }
        turnCount++;
    }

    return 0;
}



