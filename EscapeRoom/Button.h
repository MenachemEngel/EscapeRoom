#pragma once
#include "Object.h"
class Button :
	public Object
{
public:
	//c-tors and d-tor
	Button();
	virtual ~Button();
	Button(sf::Vector2f size, sf::Vector2f pos);
	//get rec function
	sf::RectangleShape& getRec();
	//set texture function
	void setTexture(std::string img);
	//drow function
	virtual void draw(sf::RenderWindow& window) override;

	sf::RectangleShape m_rec;
protected:
	sf::Texture m_tt;
};

