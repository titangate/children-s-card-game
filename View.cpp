#include "View.h"
#include <gtkmm.h>
#include <iostream>

View::View(Controller *c, Game *m) : model_(m), controller_(c), cardsPlayedVBox(true,10), topHBox(true, 10), cardsPlayedHBox(true,10), playerInfoHBox(true, 10), playerCardsHBox(true, 10), newGame_button("New game"), quit_button("Quit Game"), human_AI_rageQuit_button("Human") {

	// Sets some properties of the window.
	set_title( "Straights" );
	set_default_size(1000,600);

	add(topHBox);

	topHBox.add(newGame_button);
	// hbox.add(seed_entry);
	topHBox.add(quit_button);

	add(cardsPlayedHBox);
	cardsPlayedHBox.add(cardsPlayedVBox);
	// add card images to rows and columns

	add(playerInfoHBox);
	// group into 4 boxes
	playerInfoHBox.add(human_AI_rageQuit_button);
	playerInfoHBox.add(human_AI_rageQuit_button);
	playerInfoHBox.add(human_AI_rageQuit_button);
	playerInfoHBox.add(human_AI_rageQuit_button);
	// add score label
	// add discards label
	
	
	add(playerCardsHBox);
	// add 13 columns of card images

	

	// add actions
	// newGame_button.signal_clicked().connect(sigc::mem_fun(*this, &View::newGameButtonClicked));

	show_all(); // show button


} // View::View

/*void View::newGameButtonClicked() {
	controller_->newGameButtonClicked();
}

void View::quitGameButtonClicked() {
	controller_->quitGameButtonClicked();
} */

void View::update() {
	// card update should go here
}

View::~View() {}
