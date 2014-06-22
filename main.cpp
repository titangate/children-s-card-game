//
//  main.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-12.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include "Command.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Deck.h"
#include "Game.h"
#include <sstream>
#include <cstdlib>

using namespace std;

int main(int argc, const char * argv[])
{
    if (argc > 1) {
        Game::getInstance().setSeed(atol(argv[1]));
    } else {
        Game::getInstance().setSeed(0);
    }
    
    Game::getInstance().getDeck().reset();
    Game::getInstance().invitePlayers();
    
    while (!Game::getInstance().runRound()) {
    }
    
    return 0;
}

