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
	Game *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// member widgets
	Gtk::HBox topHBox;
	Gtk::HBox cardsPlayedHBox;
	Gtk::HBox playerInfoHBox;
	Gtk::HBox playerCardsHBox;
	Gtk::VBox cardsPlayedVBox;
	Gtk::Button newGame_button;
	Gtk::Button playCard_button;
	Gtk::ToggleButton human_AI_rageQuit_button;
	Gtk::Button quit_button;
	Gtk::Entry seed_entry;
	Gtk::Image card;

	// signal handlers
	void NewGameButtonClicked();
	void quitGameButtonClicked();

}; // View



#endif
