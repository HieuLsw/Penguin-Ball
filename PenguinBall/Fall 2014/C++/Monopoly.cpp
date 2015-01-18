//
//  Monopoly.cpp
//  test1
//
//  Created by Vaishnavi Raghu Raman on 10/15/14.
//  Copyright (c) 2014 Vaishnavi Raghu Raman. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

using namespace std;

class PlayerInfo {
public:
    double money;
    double asset;
    int position;
    double thresholdProperty;
    int thresholdHouse;
    bool isPlaying;
    vector<int> propertiesOwned;
    void AddProperty(int num)
    {
        propertiesOwned.push_back(num);
    }
    // default is the norm constructor in this case
    int GetPropertySize() {
        
        return propertiesOwned.size();
    }
   
};

class PositionData {
public:
    string positionName;
    int positionValue;
    string positionColor;
    int houses;
    double owner;
    
};


int main() {
    
    bool properInputs = true;
    int rounds = 1;
    string boardFile;
    vector<string> boardPositions;
    vector<int> boardValues;
    vector<string> boardColors;
    vector<int> boardMoves;
    
    cin >> boardFile;
    ifstream inFS;
    inFS.open(boardFile.c_str());
    
    // inports board postions, values and colors from file 1
    while(!inFS.eof()) {
        string positionCalled, color;
        int value;
        inFS >> positionCalled;
        boardPositions.push_back(positionCalled);
        inFS >> value;
        boardValues.push_back(value);
        inFS >> color;
        boardColors.push_back(color);
    }
    
    boardPositions.pop_back();
    boardValues.pop_back();
    boardColors.pop_back();
    
    inFS.close();
    
    int initialMoney;
    
    // inports the amount of money each player has initially from file 2
    string cardFile;
    cin >> cardFile;
    inFS.open(cardFile.c_str());
    inFS >> initialMoney;
    
    // inports the deck of cards still from file 2
    while(!inFS.eof()) {
        int moves;
        inFS >> moves;
        boardMoves.push_back(moves);
    }
    boardMoves.pop_back();
    inFS.close();
    
    // inports player threshold info from file 3
    string playerFile;
    cin >> playerFile;
    inFS.open(playerFile.c_str());
    vector<double> propertyThreshold;
    vector<int> houseThreshold;
    while(!inFS.eof()) {
        double propertyData;
        inFS >> propertyData;
        propertyThreshold.push_back(propertyData);
        int houseData;
        inFS >> houseData;
        houseThreshold.push_back(houseData);
    }
    propertyThreshold.pop_back();
    houseThreshold.pop_back();
    inFS.close();
    
    // get number of rounds of game
    double roundsRequested;
    cin >> roundsRequested;
    
    //checks for positive prices on boards
    
    bool iterations = true; // makes sure multiple improper input statements don't print
    
    if (iterations == true) {
    for (int i =0; i<boardValues.size();i++) {
        if (boardValues.at(i) < 0){
            cout << "Improper inputs." << endl;
            properInputs = false;
            iterations = false;
            break;
        }
    }
    }

    // checks for unknown color inputs
    if (iterations == true) {
    for (int i = 0; i < boardColors.size(); i++) {
        
        if (boardPositions.at(i) != "GO"  && boardPositions.at(i) !=
            "Parking" ) {
            if ((boardColors.at(i) == "RED") or (boardColors.at(i)
            == "BLUE") or (boardColors.at(i) == "GREEN") or (boardColors.at(i)
            == "YELLOW") or (boardColors.at(i) == "BLACK")) {
            }
            else {
            cout << "Improper inputs." << endl;
            properInputs = false;
            iterations = false;
                break;
            }
        }
    }
    }
    
    //checks to see if initial money input is a positive integer
    if (iterations == true) {
    if (initialMoney < 0 ) {
        cout << "Improper inputs." << endl;
        properInputs = false;
        iterations = false;
    }
    }

  //checks to see all cards are positive integers
    
    if (iterations == true) {
    for (int i = 0; i < boardMoves.size(); i++) {
        if ((boardMoves.at(i)) < 0) {
            cout << "Improper inputs." << endl;
            properInputs = false;
            iterations = false;
            break;
        }
    }
    }
    
    if (properInputs == true) {
    
    
// Here we create and initialize the class objects in vectors
    
    vector<PlayerInfo> player(houseThreshold.size());
    vector<PositionData> position(boardPositions.size());

    for (int i = 0; i < player.size(); i++) {
        (player.at(i)).position = 0;
        (player.at(i)).money = initialMoney;
        (player.at(i)).asset = initialMoney;
        (player.at(i)).isPlaying = true;
        (player.at(i)).thresholdProperty = (propertyThreshold.at(i));
        (player.at(i)).thresholdHouse = (houseThreshold.at(i));
        
    }
    
    for (int i = 0; i <position.size(); i++) {
        (position.at(i)).positionName = boardPositions.at(i);
        (position.at(i)).positionValue = boardValues.at(i);
        (position.at(i)).positionColor = boardColors.at(i);
        (position.at(i)).houses = 0;
        (position.at(i)).owner = 0.5;
    }

    
// Now we actually START the game
    
    cout << "***MONOPOLY GAME STARTS***" << endl;
        int p = 0;
        // loop ensures we don't go over the intended number of rounds
        for (int i = 0; (rounds <= roundsRequested)
             || ((p%(player.size())) != 0) ; i++) {
            
            int g = 0;
        for (int m = 0; m < player.size(); m++) {
            
            if ((player.at(m)).isPlaying == true) {
            g++;
            }
        }
        
        if ((g > 1) or ((p%(player.size())) != 0)) {
        
        if ((p%(player.size())) == 0) { // outputs round whenever all player have had a turn
            //(Note this works because even skipped players are counted, and increment p)
            cout << "Round: " << rounds << endl;
            rounds++;
        }
        int playerNumber = p%(player.size());
            
            // checks to see if player is still in game
            while ((player.at(playerNumber)).isPlaying == false) {
                if (playerNumber < (player.size() - 1)) {
                playerNumber++;
                    p++;
                }
                else {
                    playerNumber = 0;
                p++;
                }
                if (g <= 1 && ((p%(player.size())) == 0)) {
                    goto done;
                }
                if ((rounds > roundsRequested) && ((p%(player.size())) == 0)){
                    goto done;
                }
                if ((p%(player.size())) == 0) { // outputs round whenever all player have had a turn
                    //(Note this works because even skipped players are counted, and increment p)
                    cout << "Round: " << rounds << endl;
                    rounds++;
                }
            }
            

        int movesNumber = i%(boardMoves.size());
        int j; // stores new location
        ((player.at(playerNumber)).position += boardMoves.at(movesNumber));
            
            //cout << "      playerNumber: " << playerNumber << endl << "     movesNumber: " << movesNumber << endl;
        j = (player.at(playerNumber)).position;
            
            //cout << "      initial j: " << j << endl;
        j = j%(position.size());
            
            //cout << "      resized j:" << j << endl;
            
        cout << "Player " << playerNumber << " moves " <<
            boardMoves.at((i%(boardMoves.size()))) << " step(s) to " << boardPositions.at(j);
        //Gain $2000 if you land on go
            if (boardPositions.at(j) == "GO") {
                (player.at(playerNumber)).money += 2000;
                (player.at(playerNumber)).asset += 2000;
                cout << " and receives $2000." << endl;
            }
        //nothing happens at parking
            else if (boardPositions.at(j) == "Parking") {
            cout << " and stays." << endl;
        }
        //if property is unowned player purchases it assuming they meet the threshold
        
            else if (((position.at(j)).owner) == 0.5) {
                if (((propertyThreshold.at(playerNumber)
                      * boardValues.at(j)) < (player.at(playerNumber)).money)) {
                    ((position.at(j)).owner) = playerNumber;
                    (player.at(playerNumber)).money -= (position.at(j)).positionValue;
                    cout << " and purchases " << boardPositions.at(j) << "." << endl;
                    (player.at(playerNumber)).AddProperty(j);
                    
            }
                else {
                cout << " and stays." << endl;
            }
            }
         // if the player owns the position then he/she can build a house if they match the threashold
        // condition checks that each player can build a max of two house
            else if ((position.at(j).owner) == playerNumber) {
                if (((houseThreshold.at(playerNumber))
                     < ((player.at(playerNumber)).money))
                    && (((position.at(j)).houses) < 2 )){
                    ((player.at(playerNumber)).money) -= 1000; //player pays $1000 per house
                     ((player.at(playerNumber)).asset) -= 1000;
                    ((position.at(j)).houses) += 1; //builds one house at given position
                    
                    cout << " and builds house number " <<
                    (position.at(j)).houses << "." << endl;
                }
                else {
                    cout << " and stays." << endl;
                }
            }
        // player lands on another's property
            else {
                
                //(1) PLAYER PAYS RENT (originally 10% of price)
                double priceOwed;
                priceOwed = 0.1 * (position.at(j)).positionValue;
                
                priceOwed = static_cast<int> (priceOwed + 0.5);
                
                // Checks to see if the player has a monopoly on the property
                bool isMonopoly = true;
                 //  x stores the person # who owns the property (auto-typecast into int)
                 int x;
                  x = (position.at(j)).owner;
                 // s  stores the color at the position
                 string s;
                s = (position.at(j)).positionColor;
                 //find the other positions where we have the same color;
                 
                 for (int i = 0 ; i < boardColors.size() ; i++) {
                 if (boardColors.at(i) == s) {
                 if ((position.at(i)).owner != x) {
                 // so basically if you cannot find the position i in the porperties owned vector
                 isMonopoly = false;
                 } }}
                

                //(a)If player has monopoly then double priceOwed
                if ( isMonopoly == true) {
                    priceOwed *= 2;
                }
                //(b)Check to see if there are houses : b = 2(#houses)

                if (((position.at(j)).houses) != 0) {
                    
                    priceOwed *= (2*((position.at(j)).houses));
                }
                
                //(d)Attempt to pay rent and only words if (amount owed < amount in bank)
                if (priceOwed <= (player.at(playerNumber)).money) {
                    double x;
                    x = (position.at(j)).owner;
                    ((player.at(playerNumber)).money) =
                    ((player.at(playerNumber)).money) - priceOwed;
                    (player.at(x)).money += priceOwed;
                    ((player.at(playerNumber)).asset) =
                    ((player.at(playerNumber)).asset) - priceOwed;
                    (player.at(x)).asset += priceOwed;
                    
                    cout << " and pays $" << priceOwed << " rent to Player " << x << "." << endl;
                }
                // player moves to other's property and cannot afford the rent then properties and money are all transferred over;
                else if (priceOwed > (player.at(playerNumber)).money) {
                    
                    int z; // stores the position landed on's owner
                    z = (position.at(j)).owner;
                    
                    //transfers all money
                    (player.at(z)).money += (player.at(playerNumber)).money;
                    (player.at(z)).asset += (player.at(playerNumber)).asset;
                    (player.at(playerNumber)).money = 0;
                    (player.at(playerNumber)).asset = 0;
    
                    //properties are transfered in Player Info Class
                    ((player.at(z)).propertiesOwned).insert(
                    ((player.at(z)).propertiesOwned).end(),
                    (player.at(playerNumber).propertiesOwned).begin(),
                    (player.at(playerNumber).propertiesOwned).end());
                    
                    //properties are transferred in Position Data Class
                    
                    for (int r=0 ;
                         r < ((player.at(playerNumber)).propertiesOwned).size(); r++)
                    {
                        
                        int l; // stores the properties the player owns
                        l = ((player.at(playerNumber)).propertiesOwned).at(r);
                        (position.at(l)).owner = (position.at(j)).owner;
                        
                    }
                    
                    cout << " and bankrupt, transfers property to Player " <<
                    z << "." << endl;
                    
                    (player.at(playerNumber)).isPlaying = false;

                }
            }
            
        }

        else if (g==1) {
            break;
        }
            p++;

        }
        
    done:
        
    cout << "***SIMULATION RESULTS***" << endl;
// checks to see which player has the highest assests
    int playerMostMoney = (player.size() -1);
    int mostMoney = (player.at(player.size()-1)).asset;
    
    for (int i = (player.size() - 1); i >= 0; i--) {
        
        if ((player.at(i)).asset >= mostMoney) { // is >= to ensure that if tie lower number player is shown
            mostMoney = (player.at(i)).asset;
            playerMostMoney = i;
        }
    }
    
    cout << "Player " << playerMostMoney <<
        " wins the game with total asset value of $" <<
        mostMoney <<"." << endl;
    
    cout << "***GAME SUMMARY***" << endl;
    for (int i = 0; i < player.size() ; i++) {
        
        cout << "Player " << i << ":" << endl;
        // checks if player is bankrupt
        if ((player.at(i)).isPlaying == false) {
            cout << "Bankrupt and out of game." << endl;
            }
        else {
            cout << "Cash Balance: $" << (player.at(i)).money << endl;
            //checks if player owns property
            if ((player.at(i)).GetPropertySize() == 0){
                cout << "No purchased property." << endl;
            }
            else {
                cout << "Number of Purchased Properties: "
                << (player.at(i)).GetPropertySize() << endl;
            }
        }
    }
    }
    
    return 0;
    
}



                            

