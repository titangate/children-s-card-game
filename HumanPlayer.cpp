//
//  HumanPlayer.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "HumanPlayer.h"
#include "Command.h"
#include "Game.h"
#include <cassert>

using namespace std;

void printCardsInSuit(const string &name, const vector<Card*> cards) {
    cout << name << ":";
    const string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    bool rankExist[RANK_COUNT] = {false};
    for (int i = 0; i < cards.size(); i++) {
        rankExist[(int)cards[i]->getRank()] = true;
    }
    for (int i = 0; i < RANK_COUNT; i++) {
        if (rankExist[i]) {
            cout << " " << ranks[i];
        }
    }
    cout << endl;
}

bool HumanPlayer::pollCommand() {
    Game &game = Game::getInstance();
    cout << "Cards on the table:" << endl;
    vector<Card*> clubs, diamonds, hearts, spades;
    
    const vector<Card *>& cards = game.getCardsPlayed();
    for (int i = 0; i < cards.size(); i++) {
        switch (cards[i]->getSuit()) {
            case CLUB:
                clubs.push_back(cards[i]);
                break;
                
            case DIAMOND:
                diamonds.push_back(cards[i]);
                break;
            
            case HEART:
                hearts.push_back(cards[i]);
                break;
            
            case SPADE:
                spades.push_back(cards[i]);
                break;
            
            default:break;
        }
    }
    printCardsInSuit("Clubs", clubs);
    printCardsInSuit("Diamonds", diamonds);
    printCardsInSuit("Hearts", hearts);
    printCardsInSuit("Spades", spades);
    
    cout << "Your hand:";
    for (int i = 0; i < getHand().size(); i++) {
        cout << " " << *getHand()[i];
    }
    cout << endl;
    
    vector<Card*> valids = getLegalPlays();
    cout << "Legal Plays:";
    for (int i = 0; i < valids.size(); i++) {
        cout << " " << *valids[i];
    }
    cout << endl;
    
    return true;
}