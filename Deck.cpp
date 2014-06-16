//
//  Deck.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "Deck.h"
#include "Card.h"

void Deck::shuffle() {
    cards_.clear();
    for (int rank = ACE; rank != RANK_COUNT; rank++) {
        for (int suit = CLUB; suit != SUIT_COUNT; suit++) {
            cards_.push_back(new Card((Suit)(suit), (Rank)(rank)));
        }
    }
    int n = cards_.size();
    
	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}

}