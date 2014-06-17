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
#include <sstream>

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
        stringstream ss;
        ss << players.size();
        players.back()->setName(ss.str());
    }
    return players;
}

int dealDeck(vector<Player*> players) {
    Deck &deck = Game::getInstance().getDeck();
    int starterIndex = -1;
    for (int i = 0; i < 4; i++) {
        vector<Card*> hand;
        for (int j = 0; j < 13; j++) {
            Card *card = deck.getCardAtIndex(i * 13 + j);
            hand.push_back(card);
            
            if (card->getRank() == SEVEN && card->getSuit() == SPADE) {
                starterIndex = i;
            }
        }
        players[i]->setHand(hand);
    }
    return starterIndex;
}

bool runRound(vector<Player *>& players) {
    Game::getInstance().reset();
    int starterIndex = dealDeck(players);
    cout << "A new round begins. It's player "<< players[starterIndex]->getName() <<"'s turn to play." << endl;
    assert(starterIndex >= 0);
    for (int i = 0; i < 52; i++) {
        int currentIndex = (starterIndex + i) % players.size();
        try {
            players[currentIndex]->pollCommand();
        } catch (quit e) {
            exit(0);
        } catch (rage_quit e) {
            cout << "Player "<< players[currentIndex]->getName() << " ragequits. A computer will now take over." << endl;
            Player *player = players[currentIndex];
            Player *newPlayer = new ComputerPlayer();
            players[currentIndex] = newPlayer;
            newPlayer->setHand(player->getHand());
            newPlayer->setName(player->getName());
            newPlayer->setDiscard(player->getDiscard());
            delete player;
            i--;
        }
    }
    // produce results
    static int scores[4] = {0,0,0,0};
    int gameOver = false;
    for (int i = 0; i < players.size(); i++) {
        cout << "Player " << players[i]->getName() << "'s discards:";
        std::vector<Card*> discards = players[i]->getDiscard();
        for (int i = 0; i < discards.size(); i++) {
            cout << " " << *discards[i];
        }
        cout << endl;
        int scoreThisRound = players[i]->getScore();
        cout << "Player " << players[i]->getName() << "'s score: " << scores[i] << " + " << scoreThisRound << " = ";
        scores[i] += scoreThisRound;
        cout << scores[i] << endl;
        gameOver |= (scores[i] >= 80);
    }
    if (gameOver) {
        int minimum = 1023456789;
        for (int i = 0; i < players.size(); i++) {
            if (minimum > scores[i]) {
                minimum = scores[i];
            }
        }
        for (int i = 0; i < players.size(); i++) {
            if (minimum == scores[i]) {
                cout << "Player " << players[i]->getName() << " wins!" << endl;
            }
        }
    }
    return gameOver;
}

int main(int argc, const char * argv[])
{
    vector<Player*> players = invitePlayers();
    
    if (argc > 1) {
        Game::getInstance().setSeed(atol(argv[1]));
    } else {
        Game::getInstance().setSeed(0);
    }
    
    Game::getInstance().getDeck().reset();
    
    while (!runRound(players)) {
    }
    
    for (int i = 0; i < players.size(); i++) {
        delete players[i];
    }
    
    return 0;
}

