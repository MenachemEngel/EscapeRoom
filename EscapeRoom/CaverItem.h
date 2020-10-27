#pragma once
#include "Item.h"
class CaverItem :
	public Item
{
public:
	//c-tors and d-tors
	CaverItem();
	CaverItem(double w, double h, std::string img) : Item(img, sf::Vector2f(w, h)) {}
	CaverItem(double w, double h, std::string img ,int a[]) : Item(img, sf::Vector2f(w, h) ,a) {}
	~CaverItem();
	//move function
	virtual void move(sf::Vector2f v2f = sf::Vector2f()) override;

private:
	int num = 0;
};

