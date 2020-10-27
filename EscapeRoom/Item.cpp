#include "Item.h"
#include "Constants.h"
#include <iostream>

Item::Item(std::string str, sf::Vector2f pos)
{
	m_tt.loadFromFile(str);
	m_rec.setTexture(&m_tt, true);
	m_rec.setSize(PLAY_MENU_SIZE);
	m_rec.setPosition(pos);
	m_rec.setFillColor(sf::Color::White);
}

Item::Item(std::string str , sf::Vector2f pos ,int a[])
{
	m_tt.loadFromFile(str);
	m_rec.setTexture(&m_tt ,true);
	m_rec.setSize(PLAY_MENU_SIZE);
	m_rec.setPosition(pos);
	m_rec.setFillColor(sf::Color::White);
	for (int i = 0; i < 4; i++) {
		m_pswd[i] = a[i];
	}
}

bool Item::checkCode(int a[]) {
	for (int i = 0; i < 3; i++) {
		std::cout << m_pswd[i] << "-----" << a[i] << std::endl;
		if (m_pswd[i] != a[i]) {
			return false;
		}
	}
	return true;
}

Item::~Item()
{
}

sf::RectangleShape & Item::getRec()
{
	return m_rec;
}

void Item::draw(sf::RenderWindow & window)
{
	window.draw(m_rec);
}
