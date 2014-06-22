//
//  ComputerPlayer.h
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#ifndef __straights__ComputerPlayer__
#define __straights__ComputerPlayer__

#include <iostream>
#include "Player.h"

class ComputerPlayer : public Player {
public:
    void pollCommand();
};

#endif /* defined(__straights__ComputerPlayer__) */
