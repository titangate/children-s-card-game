//
//  Player.h
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#ifndef __straights__Player__
#define __straights__Player__

#include <iostream>
#include "Card.h"
#include <vector>

class invalid_play : public std::exception {
};

class Player {
public:
    std::vector<Card*>& getHand();
    std::vector<Card*>& getDiscard();
    virtual void pollCommand() = 0;
    int getScore();
    void setHand(const std::vector<Card*>);
    Card *findCard(Suit suit, Rank rank);
    virtual ~Player(){}
private:
    std::vector<Card*> hand_;
    std::vector<Card*> discard_;
protected:
    void play(Suit suit, Rank rank);
    void discard(Suit suit, Rank rank);
};

#endif /* defined(__straights__Player__) */
