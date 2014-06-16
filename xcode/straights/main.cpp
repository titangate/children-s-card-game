//
//  main.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-12.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include "Command.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Deck.h"
#include "Game.h"

using namespace std;

vector<Player*> invitePlayers() {
    vector<Player*> players;
    string input;
    while (players.size() < 4) {
        cout << "Is player "<< players.size() + 1 << " a human(h) or a computer(c)?" << endl;
        cout << ">";
        cin >> input;
        assert(input == "c" || input == "C" || input == "H" || input == "h");
        if (input == "h" || input == "H") {
            players.push_back(new HumanPlayer());
        } else {
            players.push_back(new ComputerPlayer());
        }
    }
    return players;
}

int dealDeck(vector<Player*> players, Deck& deck) {
    int starterIndex = -1;
    for (int i = 0; i < 4; i++) {
        vector<Card*> hand;
        for (int j = 0; j < 13; j++) {
            Card *card = deck.getCardAtIndex(i * 13 + j);
            hand.push_back(card);
            players[i]->setHand(hand);
            
            if (card->getRank() == SEVEN && card->getSuit() == SPADE) {
                starterIndex = i;
            }
        }
    }
    return starterIndex;
}

bool runRound(vector<Player *> players) {
    Game::getInstance().reset();
    Deck deck;
    deck.reset();
    deck.shuffle();
    int starterIndex = dealDeck(players, deck);
    cout << "A new round begins. It's player "<< starterIndex + 1 <<"'s turn to play." << endl;
    assert(starterIndex >= 0);
    for (int i = 0; i < 52; i++) {
        int currentIndex = (starterIndex + i) % players.size();
        try {
            players[currentIndex]->pollCommand();
        } catch (quit e) {
            exit(0);
        } catch (rage_quit e) {
            cout << "Player "<< currentIndex+1 << "ragequits. A computer will now take over." << endl;
            Player *player = players[currentIndex];
            delete player;
            players[currentIndex] = new ComputerPlayer();
            i--;
        }
    }
    // produce results
    int scores[4];
    int gameOver = false;
    for (int i = 0; i < players.size(); i++) {
        scores[i] = players[i]->getScore();
        gameOver |= (scores[i] >= 80);
    }
    return gameOver;
}

int main(int argc, const char * argv[])
{
    vector<Player*> players = invitePlayers();
    
    while (!runRound(players)) {
        
    }
    // following procedure would handle ragequit
    //players[2].reset(new ComputerPlayer());
    return 0;
}

