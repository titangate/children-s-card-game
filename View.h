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

}; // View

#endif