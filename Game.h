//
//  Game.h
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#ifndef __straights__Game__
#define __straights__Game__

#include <iostream>
#include <vector>
#include "Deck.h"
#include "Card.h"

class Game {
    
public:
    static Game& getInstance();
    void reset();
    void playCard(Card *);
    bool isPlayValid(Card *);
    std::vector<Card*> getCardsPlayed();
    void setSeed(long);
    Deck& getDeck();
private:
    std::vector<Card*> cardsPlayed_;
    bool playField_[4][13];
    Deck deck_;
    bool sevenOfSpadePlayed_;
    Game() {}
    Game(Game const&);
    void operator=(Game const&);
};

#endif /* defined(__straights__Game__) */
