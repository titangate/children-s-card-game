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

using namespace std;

vector<auto_ptr<Player>> invitePlayers() {
    vector<auto_ptr<Player>> players;
    string input;
    while (players.size() < 4) {
        cout << "Is player "<< players.size() + 1 << " a human(h) or a computer(c)?" << endl;
        cout << ">";
        cin >> input;
        assert(input == "c" || input == "C" || input == "H" || input == "h");
        if (input == "h" || input == "H") {
            players.push_back(auto_ptr<Player>(new HumanPlayer()));
        } else {
            players.push_back(auto_ptr<Player>(new HumanPlayer()));
        }
    }
    return players;
}

void dealDeck(vector<auto_ptr<Player>> players, Deck& deck) {
    
}

int main(int argc, const char * argv[])
{
    vector<auto_ptr<Player>> players = invitePlayers();
    // following procedure would handle ragequit
    //players[2].reset(new ComputerPlayer());
    return 0;
}

