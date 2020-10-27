#pragma once
#include "Object.h"
#include <memory>
#include <vector>
#include <utility>

class Item :
	public Object
{
public:
	//defoult c-tor and d-tor
	Item() {};
	virtual ~Item();
	//c-tor that get img and pos
	Item(std::string img,  sf::Vector2f pos);
	//c-tor that get img and pos and int array
	Item(std::string img,  sf::Vector2f pos ,int a[]);

	//function that return refernce to sf::RectangleShape
	sf::RectangleShape& getRec();
	//draw function from object
	virtual void draw(sf::RenderWindow& window) override;
	//function that check the code and return boolean 
	bool checkCode(int a[]);
	//function that move the item
	virtual void move(sf::Vector2f v2f = sf::Vector2f()) = 0;

protected:
	int m_pswd[4];
	sf::RectangleShape m_rec;
	sf::Texture m_tt;
};

