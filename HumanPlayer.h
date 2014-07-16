//
//  HumanPlayer.h
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#ifndef __straights__HumanPlayer__
#define __straights__HumanPlayer__

#include <iostream>
#include "Player.h"

class rage_quit : public std::exception {
};

class quit : public std::exception {
};

class HumanPlayer : public Player {
public:
    bool pollCommand();
};

#endif /* defined(__straights__HumanPlayer__) */
