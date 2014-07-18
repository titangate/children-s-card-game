#include "View.h"
#include <gtkmm.h>
#include <iostream>
#include "Controller.h"
#include "Card.h"
#include "Game.h"
#include <sstream>

using namespace std;

View::View(Controller *c, Game *m) :
game_(m),
controller_(c),
topPanel_(false, 5),
newGameButton_("New game"),
quitButton_("Quit Game"),
vbox_(false,10),
seedAdjustment_(0, 0, 1000000.0, 1.0, 5.0, 0.0),
seedSpinButton_(seedAdjustment_)
{

	// Sets some properties of the window.
	set_title( "Straights" );
	set_default_size(10,10);

	add(vbox_);
	vbox_.add(topPanel_);

	// add top panel where player can play a new game, quit the game, or enter the seed
	topPanel_.add(newGameButton_);
	topPanel_.add(seedSpinButton_);
	topPanel_.add(quitButton_);

	// add the panel for cards played in the round
	for (int i=0;i<4;i++) {
		
		Gtk::HBox* row = new Gtk::HBox(true, 0);
		vbox_.add(*row);

		for (int j=0;j<13;j++) {

			Gtk::Image* image = new Gtk::Image(deck_.null());
			image->set_padding(0,0);
			cardImages_.push_back(image);
			row->add(*image);
		}

		suits_.push_back(row);
	}

	// add the players panel that allows player to toggle between computer/human players, and view each players points and discards
	Gtk::HBox* players = new Gtk::HBox(true,0);

	for (int i=1;i<5;i++) {
		Gtk::VBox* details = new Gtk::VBox(false,0);
		
		stringstream ss;
		ss << "Player " << i;
		Gtk::Frame* playerframe = new Gtk::Frame(ss.str());

		Gtk::Label* player_points = new Gtk::Label(" points");
		Gtk::Label* player_discards = new Gtk::Label(" discards");

		Gtk::Button* player_toggle = new Gtk::Button("Human");
		playerToggleButtons_.push_back(player_toggle);
		details->add(*player_toggle);

		// add number of points
		details->add(*player_points);
		pointLabels_.push_back(player_points);

		//add number of discards
		details->add(*player_discards);
		discardLabels_.push_back(player_discards);
		
		playerframe->add(*details);
		playerInfo_.push_back(playerframe);
		players->add(*playerframe);

		player_toggle->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &View::playerStateChanged), i-1));
	}
	vbox_.add(*players);

	// add the bottom panel showing the player's current hand, and allows the player to select the card to play or discard by clicking the card
	Gtk::HBox* cards = new Gtk::HBox(true, 0);
	for (int i=0;i<13;i++) {
		Gtk::Button* button = new Gtk::Button();
		playerCards_.push_back(button);
		cards->add(*button);

		Gtk::Image *image = new Gtk::Image(deck_.null());
		image->set_padding(0,0);
		button->set_image(*image);
		playerCardImages_.push_back(image);
		button->signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &View::playCardClicked), i));
	}
	vbox_.add(*cards);

	show_all(); // show button

	game_->subscribe(this);

	// add actions
	quitButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::quitGameButtonClicked));
	newGameButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::newGameButtonClicked));

}

void View::newGameButtonClicked() {
	controller_->newGameButtonClicked(seedSpinButton_.get_value_as_int());
}

void View::quitGameButtonClicked() {
	controller_->quitGameButtonClicked();
}

void View::playerStateChanged(int index) {
	controller_->playerStateChanged(index);
	// before game begins, toggles human player to computer and vice versa
	// after game begins human player has option to ragequit on turn
}

void View::playCardClicked(int index) {
	controller_->playCardClicked(index);
}

void View::update() {
	// update the player's hand
	cout << "updating..." << endl;
	for (int i = 0; i < playerCardImages_.size(); i++) {
		playerCardImages_[i]->set(deck_.null());
	}

	for (int i = 0; i < cardImages_.size(); i++) {
		cardImages_[i]->set(deck_.null());
	}

	for (int i = 0; i < playerCardImages_.size(); i++) {
		playerCardImages_[i]->set(deck_.null());
	}
	if (game_->isGameInProgress()) {
		vector<Player*> players = game_->getPlayers();
		for (int i = 0; i < players.size(); i++)
		{
			stringstream ss;
			ss << players[i]->getAccumulatedScore() << " points";
			pointLabels_[i]->set_text(ss.str());

			ss.str("");
			ss << players[i]->getDiscard().size() << " discards";
			discardLabels_[i]->set_text(ss.str());
		}

		vector<Card*> hand = game_->getCurrentPlayer()->getHand();
		for (int i = 0; i < hand.size(); i++) {
			Card *card = hand[i];
			if (card) {
				playerCardImages_[i]->set(deck_.image(*card));
			} else {
				break;
			}
		}

		// update the player field
		vector<Card*> field = game_->getCardsPlayed();
		for (int i = 0; i < field.size(); i++) {
			Card *card = field[i];
			cardImages_[(int)card->getSuit() * 13 + (int)card->getRank()]->set(deck_.image(*card));
		}

		for (int i = 0; i < playerToggleButtons_.size(); i++) {
			playerToggleButtons_[i]->set_label("Rage!!");
			playerToggleButtons_[i]->set_sensitive(game_->getCurrentIndex() == i);
		}
	} else {
		for (int i = 0; i < playerToggleButtons_.size(); i++) {
			playerToggleButtons_[i]->set_label(game_->getInitialPlayerIsComputer(i) ? "Computer" : "Human");
			playerToggleButtons_[i]->set_sensitive(true);
		}
	}

	string message = game_->dequeMessage();
	if (message.length() > 0) {
		alert(message);
	}
}

void View::alert(const std::string &message) {
	Gtk::MessageDialog dialog(*this, message);
	dialog.run();
}

View::~View() {}
