#ifndef __straights__View__
#define __straights__View__

#include <gtkmm.h>
#include "Observer.h"
#include "DeckGUI.h"


class Controller;
class Game;

class View : public Gtk::Window, public Observer {
public:
        View( Controller*, Game* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Game accessors without having to downcast subject
	Game *game_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// member widgets
	Gtk::VBox vbox;

	Gtk::HBox topHBox;
	Gtk::Button newGame_button;
	
	std::vector<Gtk::Image*> cardImages_;
	std::vector<Gtk::HBox*> suits;
	
	std::vector<Gtk::Frame*> playerInfo;
	Gtk::ToggleButton toggle_button [4];

	std::vector<Gtk::Label*> pointLabels;
	std::vector<Gtk::Label*> discardLabels;

	std::vector<Gtk::Button*> playerCards_;
	std::vector<Gtk::Image*> playerCardImages_;

	
	Gtk::Button quit_button;
	Gtk::Adjustment seed_adjustment;
	Gtk::SpinButton seed_spinButton;
	Gtk::Image card;

	// Card Images
	DeckGUI deck;

	// signal handlers
	void newGameButtonClicked();
	void quitGameButtonClicked();
	void playCardClicked(int index);
}; // View

#endif
