#pragma once
#include "Object.h"
class Puzzle :
	public Object
{
public:
	//defoult c-tor and d-tor
	Puzzle();
	virtual ~Puzzle();
	//create function
	virtual void creat(int a[] = { 0 }) = 0;
	//onClick function
	virtual void onClick(sf::RenderWindow& window) = 0;
	//onPressed function
	virtual void onPressed(sf::RenderWindow& window ,sf::Event& event) = 0;
	//drow function
	virtual void draw(sf::RenderWindow& window) = 0;
	//isFinish function
	virtual bool isFinish() = 0;
};

