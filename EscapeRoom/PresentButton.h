#pragma once
#include "Button.h"
class PresentButton :
	public Button
{
public:
	PresentButton();
	PresentButton(sf::Vector2f s, sf::Vector2f p) : Button(s,p) {}
	virtual ~PresentButton();
	


private:
	
};

