//
//  Player.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "Player.h"
#include "Game.h"
#include <iostream>

using namespace std;

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
    discard_.clear();
}

void Player::play(Suit suit, Rank rank) {
    Game &game = Game::getInstance();
    for (int i = 0; i < hand_.size(); i++) {
        Card *card = hand_[i];
        if (suit == card->getSuit() && rank == card->getRank()) {
            if (game.isPlayValid(card)) {
                hand_.erase(hand_.begin() + i);
                game.playCard(card);
                
                cout << "Player " << getName() << " plays " << *card << "." << endl;
            } else {
                throw invalid_play();
            }
            break;
        }
    }
}

void Player::discard(Suit suit, Rank rank) {
    if (getLegalPlays().size() > 0) {
        throw invalid_play();
    }
    for (int i = 0; i < hand_.size(); i++) {
        Card *card = hand_[i];
        if (suit == card->getSuit() && rank == card->getRank()) {
            hand_.erase(hand_.begin() + i);
            discard_.push_back(card);
            cout << "Player " << getName() << " discards " << *card << "." << endl;
            break;
        }
    }
}

vector<Card*> Player::getLegalPlays() {
    Game &game = Game::getInstance();
    vector<Card*> valids;
    for (int i = 0; i < getHand().size(); i++) {
        if (game.isPlayValid(getHand()[i])) {
            valids.push_back(getHand()[i]);
        }
    }
    return valids;
}

void Player::setName(const std::string& name) {
    name_ = name;
}

std::string Player::getName() {
    return name_;
}