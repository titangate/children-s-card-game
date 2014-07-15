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
    string input;
    while (players_.size() < 4) {
        cout << "Is player "<< players_.size() + 1 << " a human(h) or a computer(c)?" << endl;
        cout << ">";
        cin >> input;
        assert(input == "c" || input == "C" || input == "H" || input == "h");
        if (input == "h" || input == "H") {
            players_.push_back(new HumanPlayer());
        } else {
            players_.push_back(new ComputerPlayer());
        }
        stringstream ss;
        ss << players_.size();
        players_.back()->setName(ss.str());
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
    while (getCurrentPlayer()->pollCommand()) {
        runGameUntilInputRequired();
    }
}

void Game::endRound() {
    // produce results
    static int scores[4] = {0,0,0,0};
    int gameOver = false;
    for (int i = 0; i < players_.size(); i++) {
        cout << "Player " << players_[i]->getName() << "'s discards:";
        std::vector<Card*> discards = players_[i]->getDiscard();
        for (int i = 0; i < discards.size(); i++) {
            cout << " " << *discards[i];
        }
        cout << endl;
        int scoreThisRound = players_[i]->getScore();
        cout << "Player " << players_[i]->getName() << "'s score: " << scores[i] << " + " << scoreThisRound << " = ";
        scores[i] += scoreThisRound;
        cout << scores[i] << endl;
        gameOver |= (scores[i] >= 80);
    }
    if (gameOver) {
        int minimum = 1023456789;
        for (int i = 0; i < players_.size(); i++) {
            if (minimum > scores[i]) {
                minimum = scores[i];
            }
        }
        for (int i = 0; i < players_.size(); i++) {
            if (minimum == scores[i]) {
                cout << "Player " << players_[i]->getName() << " wins!" << endl;
            }
        }
    } else {
        runRound();
    }
}

void Game::runRound() {
    Game::getInstance().reset();
    int starterIndex = dealDeck();
    cout << "A new round begins. It's player "<< players_[starterIndex]->getName() <<"'s turn to play." << endl;
    assert(starterIndex >= 0);

    runGameUntilInputRequired();
}