//
//  Player.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "Player.h"

std::vector<Card*> Player::getHand() {
    return hand_;
}

std::vector<Card*> Player::getDiscard() {
    return discard_;
}

int Player::getScore() {
    int score = 0;
    for (int i = 0; i < discard_.size(); i++) {
        score += discard_[i]->getRank() + 1;
    }
    return score;
}

void Player::setHand(const std::vector<Card*> hand) {
    hand_ = hand;
}