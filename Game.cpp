//
//  Game.cpp
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#include "Game.h"
#include "Card.h"
#include <cstdlib>
#include <cassert>
#include <sstream>
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

Game::Game() {
    gameInProgress_ = false;
    for (int i = 0; i < 4; i++) {
        initialPlayers_[i] = false;
    }
}

void Game::reset() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            playField_[i][j] = false;
        }
    }
    playField_[(int)CLUB][(int)SEVEN] = true;
    playField_[(int)SPADE][(int)SEVEN] = true;
    playField_[(int)HEART][(int)SEVEN] = true;
    playField_[(int)DIAMOND][(int)SEVEN] = true;
    sevenOfSpadePlayed_ = false;
    
    deck_.shuffle();
    cardsPlayed_.clear();
}

void Game::playCard(Card *c) {
    sevenOfSpadePlayed_ = true;
    cardsPlayed_.push_back(c);
    int suitId = (int)c->getSuit();
    int rankId = (int)c->getRank();
    
    if (rankId > 0) {
        playField_[suitId][rankId - 1] = true;
    }
    if (rankId < 12) {
        playField_[suitId][rankId + 1] = true;
    }
}

bool Game::isPlayValid(Card *c) {
    if (!sevenOfSpadePlayed_) {
        return c->getRank() == SEVEN && c->getSuit() == SPADE;
    }
    int suitId = (int)c->getSuit();
    int rankId = (int)c->getRank();
    return playField_[suitId][rankId];
}

Deck& Game::getDeck() {
    return deck_;
}

vector<Card*> Game::getCardsPlayed() {
    return cardsPlayed_;
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Player* Game::getCurrentPlayer() {
    return players_[currentIndex];
}

void Game::setSeed(long seed) {
    srand48(seed);
    cout << "Seed is set to " << seed << endl;
}

void Game::invitePlayers() {
    for (int i = 0; i < 4; ++i)
    {
        if (initialPlayers_[i]) {
            players_.push_back(new ComputerPlayer());
        } else {
            players_.push_back(new HumanPlayer());
        }
    }
}

int Game::dealDeck() {
    Deck &deck = Game::getInstance().getDeck();
    int starterIndex = -1;
    for (int i = 0; i < 4; i++) {
        vector<Card*> hand;
        for (int j = 0; j < 13; j++) {
            Card *card = deck.getCardAtIndex(i * 13 + j);
            hand.push_back(card);
            
            if (card->getRank() == SEVEN && card->getSuit() == SPADE) {
                starterIndex = i;
            }
        }
        players_[i]->setHand(hand);
    }
    return starterIndex;
}

Game::~Game() {
    for (int i = 0; i < players_.size(); i++) {
        delete players_[i];
    }
}

void Game::issueCommand(const Command& command) {
    getCurrentPlayer()->processCommand(command);
    turnCount++;
    runGameUntilInputRequired();
}

void Game::rageQuit() {
    cout << "Player "<< getCurrentPlayer()->getName() << " ragequits. A computer will now take over." << endl;
    Player *player = getCurrentPlayer();
    Player *newPlayer = new ComputerPlayer();
    players_[currentIndex] = newPlayer;
    newPlayer->setHand(player->getHand());
    newPlayer->setName(player->getName());
    newPlayer->setDiscard(player->getDiscard());
    delete player;
    currentIndex = (currentIndex - 1) % players_.size();
    
    notify();

    runGameUntilInputRequired();
}

void Game::runGameUntilInputRequired() {
    currentIndex = (currentIndex + 1) % players_.size();
    cout << "Player " << currentIndex << "'s turn" << endl;
    notify();
    while (!getCurrentPlayer()->pollCommand() && turnCount < 52) {
        turnCount++;
        runGameUntilInputRequired();
    }
}

void Game::endRound() {
    // produce results
    int gameOver = false;
    stringstream ss;
    for (int i = 0; i < players_.size(); i++) {
        ss << "Player " << players_[i]->getName() << "'s discards:";
        std::vector<Card*> discards = players_[i]->getDiscard();
        for (int i = 0; i < discards.size(); i++) {
            ss << " " << *discards[i];
        }
        ss << endl;
        int scoreThisRound = players_[i]->getScore();
        ss << "Player " << players_[i]->getName() << "'s score: " << players_[i]->getScore() << " + " << scoreThisRound << " = ";
        players_[i]->setAccumulatedScore(players_[i]->getAccumulatedScore() + scoreThisRound);
        ss << players_[i]->getAccumulatedScore() << endl;
        gameOver |= (players_[i]->getAccumulatedScore() >= 80);
    }
    alertMessage_ = ss.str();
    notify();
    if (gameOver) {
        int minimum = 1023456789;
        for (int i = 0; i < players_.size(); i++) {
            if (minimum > players_[i]->getScore()) {
                minimum = players_[i]->getScore();
            }
        }
        for (int i = 0; i < players_.size(); i++) {
            if (minimum == players_[i]->getScore()) {
                stringstream ss;
                ss << "Player " << players_[i]->getName() << " wins!" << endl;
                alertMessage_ = ss.str();
                notify();
            }
        }
    } else {
        runRound();
    }
}

void Game::endCurrentRound() {
    gameInProgress_ = false;
}

void Game::runRound() {
    turnCount = 0;
    gameInProgress_ = true;
    Game::getInstance().reset();
    currentIndex = dealDeck();
    cout << "A new round begins. It's player "<< players_[currentIndex]->getName() <<"'s turn to play." << endl;
    assert(currentIndex >= 0);
    currentIndex--;
    runGameUntilInputRequired();
}

std::string Game::dequeMessage() {
    string temp = alertMessage_;
    alertMessage_ = "";
    return temp;
}

std::vector<Player*> Game::getPlayers() {
    return players_;
}

bool Game::isGameInProgress() {
    return gameInProgress_;
}

void Game::playerStateChanged(int index) {
    if (gameInProgress_) {

    } else {
        initialPlayers_[index] = !initialPlayers_[index];
    }
    notify();
}

bool Game::getInitialPlayerIsComputer(int index) {
    return initialPlayers_[index];
}