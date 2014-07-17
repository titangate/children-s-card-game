//
//  Game.h
//  straights
//
//  Created by Nanyi Jiang on 2014-06-16.
//  Copyright (c) 2014 Nanyi Jiang. All rights reserved.
//

#ifndef __straights__Game__
#define __straights__Game__

#include <iostream>
#include <vector>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Subject.h"
#include "Command.h"

class Game : public Subject {
    
public:
    static Game& getInstance();
    ~Game();
    void reset();
    void playCard(Card *);
    bool isPlayValid(Card *);
    std::vector<Card*> getCardsPlayed();
    std::string dequeMessage();
    void setSeed(long);
    void issueCommand(const Command&);
    void runGameUntilInputRequired();
    void invitePlayers();
    void runRound();
    void endRound();
    void endCurrentRound();
    void rageQuit();
    void playerStateChanged(int index);
    Deck& getDeck();
    Player* getCurrentPlayer();
    int getCurrentIndex();
    std::vector<Player*> getPlayers();
    bool isGameInProgress();
    bool getInitialPlayerIsComputer(int index);
private:
    std::vector<Card*> cardsPlayed_;
    std::vector<Player*> players_;
    std::string alertMessage_;
    bool gameInProgress_;
    int currentIndex;
    int turnCount;
    
    int dealDeck();
    bool playField_[4][13];
    bool initialPlayers_[4];
    Deck deck_;
    bool sevenOfSpadePlayed_;
    Game();
    Game(Game const&);
    void operator=(Game const&);
};

#endif /* defined(__straights__Game__) */
