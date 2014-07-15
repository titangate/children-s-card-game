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
	Card *card = getCardAtIndex(index);
	if (card) {
		Command cmd;
		cmd.type = PLAY;
		cmd.card = *card;
		game_->getCurrentPlayer()->processCommand(cmd);
	}
}

void Controller::discardCardClicked(int index) {
	Card *card = getCardAtIndex(index);
	if (card) {
		Command cmd;
		cmd.type = DISCARD;
		cmd.card = *card;
		game_->getCurrentPlayer()->processCommand(cmd);
	}
}

void Controller::rageClicked(int index) {
	game_->rageQuit();
}

void Controller::newGameButtonClicked(long seed) {
	game_->setSeed(seed);
	Game::getInstance().runRound();
}

void Controller::quitGameButtonClicked() {
	exit(0);
}

Card* Controller::getCardAtIndex(int index) {
	if (index < game_->getCurrentPlayer()->getHand().size()) {
		return game_->getCurrentPlayer()->getHand()[index];
	}
	return NULL;
}