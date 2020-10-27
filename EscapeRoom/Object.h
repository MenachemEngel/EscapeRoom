#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

class Object
{
public:
	Object();
	~Object();

	virtual void draw(sf::RenderWindow& window) = 0;
};

