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
	Gtk::VBox vbox_;

	Gtk::HBox topPanel_;
	Gtk::Button newGameButton_;
	Gtk::Button quitButton_;
	Gtk::Adjustment seedAdjustment_;
	Gtk::SpinButton seedSpinButton_;
	
	std::vector<Gtk::Image*> cardImages_;
	
	std::vector<Gtk::HBox*> suits_;
	
	std::vector<Gtk::Frame*> playerInfo_;
	std::vector<Gtk::Button*> playerToggleButtons_;
	std::vector<Gtk::Label*> pointLabels_;
	std::vector<Gtk::Label*> discardLabels_;

	std::vector<Gtk::Button*> playerCards_;
	std::vector<Gtk::Image*> playerCardImages_;

	// Card Images
	DeckGUI deck_;

	// signal handlers
	void newGameButtonClicked();
	void quitGameButtonClicked();
	void playCardClicked(int index);
	void playerToggleClicked(int index);
	void alert(const std::string &message);
	void playerStateChanged(int index);
}; // View

#endif
