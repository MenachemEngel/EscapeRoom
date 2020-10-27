#pragma once
#include "Item.h"


class OpenItem :
	public Item
{
public:
	OpenItem();
	OpenItem(double w, double h, std::string img) : Item(img, sf::Vector2f(w, h)) {}
	OpenItem(double w, double h, std::string img ,int a[]) : Item(img, sf::Vector2f(w, h) ,a) {}
	virtual void move(sf::Vector2f v2f = sf::Vector2f()) override;
	virtual ~OpenItem();
};

