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
	if (!game_->isGameInProgress()) return;
	Card *card = getCardAtIndex(index);
	if (card) {
		Command cmd;
		cmd.type = PLAY;
		cmd.card = *card;
		try {
			game_->issueCommand(cmd);
		} catch (invalid_play e) {
			discardCardClicked(index);
		}
	}
}

void Controller::discardCardClicked(int index) {
	if (!game_->isGameInProgress()) return;
	Card *card = getCardAtIndex(index);
	if (card) {
		Command cmd;
		cmd.type = DISCARD;
		cmd.card = *card;
		try {
			game_->issueCommand(cmd);
		} catch (invalid_play e) {
			std::cout << "Invalid play." << std::endl;
		}
	}
}

void Controller::newGameButtonClicked(long seed) {
	game_->setSeed(seed);
    Game::getInstance().getDeck().reset();
    Game::getInstance().invitePlayers();
	Game::getInstance().runRound();
}

void Controller::playerStateChanged(int index) {
	game_->playerStateChanged(index);
}

void Controller::quitGameButtonClicked() {
	if (!game_->isGameInProgress()) return;
	game_->endCurrentRound();
}

Card* Controller::getCardAtIndex(int index) {
	if (index < game_->getCurrentPlayer()->getHand().size()) {
		return game_->getCurrentPlayer()->getHand()[index];
	}
	return NULL;
}
