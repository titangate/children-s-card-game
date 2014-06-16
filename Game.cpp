//
//  Game.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "Game.h"
#include "Card.h"

using namespace std;

void Game::reset() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            playField_[i][j] = false;
        }
    }
    playField_[(int)SPADE][(int)SEVEN] = true;
}

void Game::playCard(Card *c) {
    cardsPlayed_.push_back(c);
    int suitId = (int)c->getSuit();
    int rankId = (int)c->getRank();
    
    for (int i = 0; i < 13; i++) {
        playField_[suitId][i] = true;
    }
    for (int j = 0; j < 4; j++) {
        playField_[j][rankId] = true;
    }
}

bool Game::isPlayValid(Card *c) {
    int suitId = (int)c->getSuit();
    int rankId = (int)c->getRank();
    return playField_[suitId][rankId];
}

vector<Card*> Game::getCardsPlayed() {
    return cardsPlayed_;
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}