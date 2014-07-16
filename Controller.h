//
//  Controller.h
//  straights
//
//  Created by Nanyi Jiang on 2014-07-10.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#ifndef __straights__Controller__
#define __straights__Controller__

#include <gtkmm.h>

class Game;
class Card;

class Controller {
public:
    Controller( Game* );
    void playCardClicked(int index);
    void discardCardClicked(int index);
    void rageClicked(int index);
    void newGameButtonClicked(long seed);
    void quitGameButtonClicked();
private:
	Card* getCardAtIndex(int index);
    Game *game_;
}; // Controller

#endif /* defined(__straights__Controller__) */
