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
#include <gtkmm/main.h>
#include "Controller.h"
#include "View.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc > 1) {
        Game::getInstance().setSeed(atol(argv[1]));
    } else {
        Game::getInstance().setSeed(0);
    }
    
    // Game::getInstance().getDeck().reset();
    // Game::getInstance().invitePlayers();
    
    // while (!Game::getInstance().runRound()) {
    // }
    
	Gtk::Main kit( argc, argv );         // Initialize gtkmm with the command line arguments, as appropriate.
    Controller controller( &Game::getInstance() );  // Create controller
	View view( &controller, &Game::getInstance() );     // Create the view -- is passed handle to controller and model
	Gtk::Main::run( view );               // Show the window and return when it is closed.
	
    return 0;
}

