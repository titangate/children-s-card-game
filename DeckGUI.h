#ifndef _DECK_GUI_H_
#define _DECK_GUI_H_

#include <gdkmm/pixbuf.h>
#include <vector>
#include "Card.h"
using std::vector;

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> image(const Card &card);   // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> null();                 // Returns the image to use for the placeholder.
private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;
};
#endif