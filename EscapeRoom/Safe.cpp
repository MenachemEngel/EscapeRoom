#include "safe.h"
#include "Constants.h"
#include <iostream>
#include <iostream>

Safe::Safe()
{
	for (int i = 0; i < m_rec.size(); i++) {
		m_rec[i].setSize(sf::Vector2f(WINDOW_SIZE_W / 10 , WINDOW_SIZE_W / 10));
		m_rec[i].setPosition(WINDOW_SIZE_W/6 + i*(WINDOW_SIZE_W / 6), WINDOW_SIZE_H/4);
		m_tt[i].loadFromFile("numbers//0.png");
		m_rec[i].setTexture(&m_tt[i],true);
	}
}

Safe::~Safe()
{
}

void Safe::onPressed(sf::RenderWindow & window, sf::Event & event)
{
}

bool Safe::isFinish()
{
	for (int i = 0; i < 4; i++) {
		if (m_passwd[i] != m_sPasswd[i])
			return false;
	}
	return true;
}

void Safe::onClick(sf::RenderWindow& window)
{
	sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	for (int i = 0; i < getRecs().size(); i++) {
		if (getRecs()[i].getGlobalBounds().contains(v2f)) {
			incNum(i);
		}
	}	
}

void Safe::incNum(int i) {
	if (m_sPasswd[i] == 9) {
		m_sPasswd[i] = 0;		
	}
	else {
		m_sPasswd[i]++;
		}
	}

std::vector<sf::RectangleShape> Safe::getRecs() const
{
	return m_rec;
}

void Safe::creat(int a[])
{
	for (int i = 0; i < 4; i++) {
		m_passwd[i] = a[i];
	}
}

void Safe::loadPasswd()
{
	for (int i = 0; i < m_tt.size(); i++) {
		std::string str("numbers//" + std::to_string(m_sPasswd[i]));
		m_tt[i].loadFromFile(str + ".png");
		m_rec[i].setTexture(&m_tt[i] ,true);
	}
}

void Safe::draw(sf::RenderWindow & window)
{
	loadPasswd();
	if (!isFinish()) {
		for (int i = 0; i < m_rec.size(); i++) {
			window.draw(m_rec[i]);
		}
	}
}
