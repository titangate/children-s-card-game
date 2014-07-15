#include "View.h"
#include <gtkmm.h>
#include <iostream>
#include "Controller.h"
#include "Card.h"
#include "Game.h"
#include <sstream>

using namespace std;

View::View(Controller *c, Game *m) : game_(m), controller_(c), topHBox(false, 10), newGame_button("New game"), quit_button("Quit Game"), vbox(false,10),
seed_adjustment(0, 0, 1000000.0, 1.0, 5.0, 0.0),
seed_spinButton(seed_adjustment)
{

	// Sets some properties of the window.
	set_title( "Straights" );
	set_default_size(1000,600);

	add(vbox);
	vbox.add(topHBox);

	topHBox.add(newGame_button);
	topHBox.add(seed_spinButton);
	topHBox.add(quit_button);

	for (int i=0;i<4;i++) {
		
		Gtk::HBox* row = new Gtk::HBox(true, 10);
		vbox.add(*row);

		for (int j=0;j<13;j++) {

			Gtk::Image* image = new Gtk::Image("test");
			cardImages_.push_back(image);
			row->add(*image);
		}

		suits.push_back(row);
	}
	// TODO: add images for each card



	Gtk::HBox* playerDetails = new Gtk::HBox(true,10);

	for (int i=1;i<5;i++) {
		stringstream ss;
		ss << "player" << i;
		Gtk::Frame* playerframe = new Gtk::Frame(ss.str());
		playerInfo.push_back(playerframe);
		playerDetails->add(*playerframe);
		
	}
	vbox.add(*playerDetails);
	// add actions
	// newGame_button.signal_clicked().connect(sigc::mem_fun(*this, &View::newGameButtonClicked));
	quit_button.signal_clicked().connect(sigc::mem_fun(*this, &View::quitGameButtonClicked));
	newGame_button.signal_clicked().connect(sigc::mem_fun(*this, &View::newGameButtonClicked));



	Gtk::HBox* cards = new Gtk::HBox(true, 10);
	for (int i=0;i<13;i++) {
		Gtk::Button* button = new Gtk::Button("card"); // TODO add buttons
		playerCards_.push_back(button);
		cards->add(*button);
	}
	vbox.add(*cards);

	show_all(); // show button
} // View::View

void View::newGameButtonClicked() {
	controller_->newGameButtonClicked(seed_spinButton.get_value_as_int());
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
