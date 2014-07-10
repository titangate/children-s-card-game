#include "View.h"

View::View(Controller *c, Game *m) : model_(m), controller_(c) {

	// Sets some properties of the window.
	set_title( "Straights" );
} // View::View

void View::update() {
	// card update should go here
}

View::~View() {}
