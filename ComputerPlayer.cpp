//
//  ComputerPlayer.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "ComputerPlayer.h"
#include <vector>

using namespace std;

bool ComputerPlayer::pollCommand() {
    vector<Card*> legalPlays = getLegalPlays();
    if (legalPlays.size() > 0) {
        Card *card = legalPlays[0];
        play(card->getSuit(), card->getRank());
    } else {
        Card *card = getHand()[0];
        discard(card->getSuit(), card->getRank());
    }
    return false;
}