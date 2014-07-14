//
//  Controller.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-07-10.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "Controller.h"
#include "Game.h"


Controller::Controller(Game *m) : game_(m) {}

void Controller::playCardClicked(int index) {

}

void Controller::rageClicked(int index) {

}

void Controller::newGameButtonClicked(long seed) {
	game_->setSeed(seed);
	while (!Game::getInstance().runRound()) {
    }
}

void Controller::quitGameButtonClicked() {

}