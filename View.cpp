#include "View.h"
#include <gtkmm.h>
#include <iostream>
#include "Controller.h"
#include "Card.h"
#include "Game.h"

using namespace std;

View::View(Controller *c, Game *m) : game_(m), controller_(c), topHBox(false, 10), newGame_button("New game"), quit_button("Quit Game"), vbox(false,10), cardsPlayed(false, 10), playerInfo(false, 10), playerCardsHBox(false, 10),  human_AI_rageQuit_button("Human") {

	// Sets some properties of the window.
	set_title( "Straights" );
	set_default_size(1000,600);

	add(vbox);
	vbox.add(topHBox);

	topHBox.add(newGame_button);
	topHBox.add(seed_entry);
	topHBox.add(quit_button);

	for (int i=0;i<4;i++) {
		
		Gtk::HBox* suit = new Gtk::HBox(true, 10);
		vbox.add(*suit);

		for (int j=0;j<13;j++) {

			Gtk::Image* image = new Gtk::Image("test");
			cardImages_.push_back(image);
			suit->add(*image);
			

		}

		suits.push_back(suit);
	}
	// TODO: addimages for each card

	vbox.add(playerInfo);

	// group into 4 boxes
	
	// add score label
	// add discards label
	
	
	
	// add 13 columns of card images

	

	// add actions
	// newGame_button.signal_clicked().connect(sigc::mem_fun(*this, &View::newGameButtonClicked));

	show_all(); // show button


} // View::View

void View::newGameButtonClicked() {
	controller_->newGameButtonClicked(0);
}

void View::quitGameButtonClicked() {
	controller_->quitGameButtonClicked();
}

void View::update() {
	// update the player's hand
	vector<Card*> hand = game_->getCurrentPlayer()->getHand();
	for (int i = 0; i < hand.size(); i++) {

	}

	// update the player field
	
}

View::~View() {}
