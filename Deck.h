//
//  Deck.h
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#ifndef __straights__Deck__
#define __straights__Deck__

#include <vector>
#include "Card.h"

class Deck {
public:
    Card* getCardAtIndex(int i);
    void shuffle();
    void reset();
    void print();
    
private:
    std::vector<Card *> cards_;
};

#endif /* defined(__straights__Deck__) */
