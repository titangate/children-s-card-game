#ifndef __straights__View__
#define __straights__View__

#include <gtkmm.h>
#include "Observer.h"


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
	Gtk::ToggleButton playerToggle_button [4];
	Gtk::Label player_points [4];
	Gtk::Label player_discards [4];

	std::vector<Gtk::Image*> playerCards_;

	
	Gtk::Button quit_button;
	Gtk::Entry seed_entry;
	Gtk::Image card;

	// signal handlers
	void newGameButtonClicked();
	void quitGameButtonClicked();

}; // View



#endif
