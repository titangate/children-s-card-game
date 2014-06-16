//
//  Player.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "Player.h"
#include "Game.h"

std::vector<Card*>& Player::getHand() {
    return hand_;
}

std::vector<Card*>& Player::getDiscard() {
    return discard_;
}

int Player::getScore() {
    int score = 0;
    for (int i = 0; i < discard_.size(); i++) {
        score += discard_[i]->getRank() + 1;
    }
    return score;
}

Card* Player::findCard(Suit suit, Rank rank) {
    for (int i = 0; i < hand_.size(); i++) {
        Card *card = hand_[i];
        if (suit == card->getSuit() && rank == card->getRank()) {
            return card;
        }
    }
    return NULL;
}

void Player::setHand(const std::vector<Card*> hand) {
    hand_ = hand;
}

void Player::play(Suit suit, Rank rank) {
    Game &game = Game::getInstance();
    Card *handCard = findCard(suit, rank);
        if (game.isPlayValid(handCard)) {
            game.playCard(handCard);
        } else {
            throw invalid_play();
        }
}

void Player::discard(Suit suit, Rank rank) {
    Card *handCard = findCard(suit, rank);
}