#pragma once
#include "Board.h"
#include "PlayMenu.h"
#include "StartMenu.h"
#include "ActionButton.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <SFML/Audio.hpp>
//#include "OpenItem.h"
//#include "LockItem.h"

class Controller
{
public:
	//c-tor and d-tor
	Controller();
	~Controller();
	//run function
	void run();
	//play function
	void play();
	//load function
	void loadSound();
	//finishGane function
	void finishGame();
	//check if finish function
	void checkIfFinish();
	//failure function
	void failure();

	static sf::Font m_font;
	static std::map<std::string, sf::Sound> m_sound;
private:
	sf::RenderWindow m_window;
	Board m_board;
	PlayMenu m_playMenu;
	StartMenu m_startMenu;
	sf::Event m_event;
	sf::RectangleShape m_recBackground;
	sf::Texture m_tBackground;
	sf::Music m_music[2];
	ActionButton m_ab;
	sf::Clock m_clock;	
	sf::Text m_tclock;
	sf::Sound m_ts;
	sf::SoundBuffer m_tsb[6];
	bool finish = true;
};

