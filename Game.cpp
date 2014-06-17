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
    playField_[(int)CLUB][(int)SEVEN] = true;
    playField_[(int)SPADE][(int)SEVEN] = true;
    playField_[(int)HEART][(int)SEVEN] = true;
    playField_[(int)DIAMOND][(int)SEVEN] = true;
    sevenOfSpadePlayed_ = false;
    
    deck_.shuffle();
}

void Game::playCard(Card *c) {
    sevenOfSpadePlayed_ = true;
    cardsPlayed_.push_back(c);
    int suitId = (int)c->getSuit();
    int rankId = (int)c->getRank();
    
    if (rankId > 0) {
        playField_[suitId][rankId - 1] = true;
    }
    if (rankId < 12) {
        playField_[suitId][rankId + 1] = true;
    }
}

bool Game::isPlayValid(Card *c) {
    if (!sevenOfSpadePlayed_) {
        return c->getRank() == SEVEN && c->getSuit() == SPADE;
    }
    int suitId = (int)c->getSuit();
    int rankId = (int)c->getRank();
    return playField_[suitId][rankId];
}

Deck& Game::getDeck() {
    return deck_;
}

vector<Card*> Game::getCardsPlayed() {
    return cardsPlayed_;
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::setSeed(long seed) {
    srand48(seed);
}