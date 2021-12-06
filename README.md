# **UNO** The Game
This project implements the popular family card game **UNO** into a Command-Line-Interface.
Compatbility: Common Platform (UNIX) and Windows

## How to compile:
1) Run CMake on the directory
2) use the make command
3) open UNOgame

## **Rules:**

1) **UNO** starts with *each* **player** being dealt **7** cards from the **deck**. Then, a single card from the **deck** is placed into the **play stack**.
    
2) Then, **players** go in turns placing cards onto the **play stack**. To place a card, either the **color** or **number** must match the top card in the **play stack**
    
3) If a **player** has no cards that that can be put into the **play stack**, then they draw a card from the **deck**
    
4) Once a **player** has **one** card remaining, that **player** has **UNO**
    
5) Once a **player** has **no** cards remaining, that **player** has **won**
    
    
## **Special Cards:**

There are a number of **special cards** that have unique attributes. Typically, these cards have their own color (Wild) though some are limited to a specific color.

### **Wild Cards**
1) Draw 4: This card allows the **player** to change the active **color** and cause the **next player** to draw **4 cards**
                        
3) Wild: This card allows the **player** to change the active **color**
            
### **Color Cards**
            
1) Skip: This card causes the **next player** to be skipped
            
2) Reverse: This card reverses the turn order.
            
3) Draw 2: This card causes the **next player** to draw **2 cards** that player is then skipped 
            
## Interesting Features:

### Features of this project that may not be expected or provide something unique
    
1) Multiple players. Entering multiple players will allow them to enter their name and be added to the turn order
2) Spectate. User can allow AI opponents to play on their own.
3) Mixed matches. Any number of real players and bots (up to a combined maximum of 4) can play together.
            
## Changes:

### Not all features of UNO work in this format, the following changes to the default rules have been made:
        
1) Players can not be penalized for not saying UNO when they only have one card remaining; the game does this automatically.
2) Players can look in the terminal's history to see other human player's hands.

## Status:

### Known issues with the program
    
1) Players can see previous player's hands in the terminal history. (Unable to delete terminal history)
2) The program is limited to 4 players. (A standard UNO deck is fit for up to 4 players, and this program only utilizes one deck)
3) Readibility and general UX could use further improvement.
