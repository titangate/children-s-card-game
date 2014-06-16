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

void HumanPlayer::pollCommand() {
    Game &game = Game::getInstance();
    cout << "Cards on the table:" << endl;
    const vector<Card *>& cards = game.getCardsPlayed();
    for (int i = 0; i < cards.size(); i++) {
        cout << " " << *cards[i];
    }
    cout << endl;
    
    vector<Card*> valids;
    cout << "Your hand:";
    for (int i = 0; i < getHand().size(); i++) {
        cout << " " << *getHand()[i];
        if (game.isPlayValid(getHand()[i])) {
            valids.push_back(getHand()[i]);
        }
    }
    cout << endl;
    
    cout << "Legal plays:";
    for (int i = 0; i < valids.size(); i++) {
        cout << " " << *valids[i];
    }
    cout << endl;
    
    cout << ">";
    Command command;
    bool done = false;
    while (!done) {
        cin >> command;
        switch (command.type) {
            case PLAY: {
                Card &card = command.card;
                try {
                    play(card.getSuit(), card.getRank());
                    done = true;
                } catch (invalid_play e) {
                    cout << "You have a legal play. You may not discard." << endl;
                }
            }
                break;
            case DISCARD: {
                Card &card = command.card;
                Card *handCard = findCard(card.getSuit(), card.getRank());
            }
                break;
            case DECK:
                done = true;
                break;
            case QUIT:
                throw quit();
                break;
            case RAGEQUIT:
                throw rage_quit();
                break;
            default:
                break;
        }
    }
}