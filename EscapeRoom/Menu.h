#pragma once
#include "Object.h"
#include "Board.h"

class Controller;

class Menu :
	public Object
{
public:
	Menu();
	virtual ~Menu();

	virtual void onClick(sf::RenderWindow& window, sf::Event& event, Board& board, Controller& ctrl) = 0;
	virtual void onOver(sf::RenderWindow&, sf::Event&) = 0;
};

