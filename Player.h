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

class Player {
public:
    std::vector<Card*> getHand();
    std::vector<Card*> getDiscard();
    virtual void pollCommand() = 0;
    int getScore();
    void setHand(const std::vector<Card*>);
private:
    std::vector<Card*> hand_;
    std::vector<Card*> discard_;
};

#endif /* defined(__straights__Player__) */
