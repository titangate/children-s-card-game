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
    int n = cards_.size();
    
	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

void Deck::reset() {
    for (int i = 0; i < cards_.size(); i++) {
        delete cards_[i];
    }
    cards_.clear();
    
    for (int rank = ACE; rank != RANK_COUNT; rank++) {
        for (int suit = CLUB; suit != SUIT_COUNT; suit++) {
            cards_.push_back(new Card((Suit)(suit), (Rank)(rank)));
        }
    }
}

Card* Deck::getCardAtIndex(int i) {
    return cards_[i];
}