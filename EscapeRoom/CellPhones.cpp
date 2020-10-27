#include "CellPhones.h"
#include "Constants.h"
#include <iostream>

void CellPhones::creat(int a[])
{
	sf::Vector2f v(270.f, 500.f);
	sf::Vector2f v1(sf::VideoMode::getDesktopMode().width / 1.4, sf::VideoMode::getDesktopMode().height / 1.4);
	m_t[0].loadFromFile(CELLPHONES[0]);
	m_rs[0].setTexture(&m_t[0]);
	m_rs[0].setPosition(0, 0);
	m_rs[0].setSize(v1);
	for (int i = 1; i < 4; i++)
	{
		m_t[i].loadFromFile(CELLPHONES[i]);
		m_rs[i].setTexture(&m_t[i]);
		if (i == 1)
		{
			m_rs[i].setPosition(370, 30);
			m_rs[i].setSize(v);
		}
		if (i == 2 || i == 3)
		{
			m_rs[i].setPosition(400, 250);
			m_rs[i].setSize(sf::Vector2f(30.f, 30.f));
		}
	}
	m_isClick = false;
	m_temp_rs = m_rs;
}

void CellPhones::onClick(sf::RenderWindow &window)
{
	if (m_temp_rs[1].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		m_isClick = true;
	}
}

void CellPhones::setClick()
{
	if (m_temp_rs[2].getTexture() == m_rs[2].getTexture())
		m_temp_rs[2].setTexture(m_rs[3].getTexture());
	else
		m_temp_rs[2].setTexture(m_rs[2].getTexture());
}

void CellPhones::draw(sf::RenderWindow &window)
{

	for (int i = 0; i < 3; i++)
		window.draw(m_temp_rs[i]);
	window.draw(m_text);
	if (getIsClick() && clock.getElapsedTime().asSeconds() - m_prevTime > 0.3)
		{
			m_prevTime = clock.getElapsedTime().asSeconds();
			setClick();
		}
}

bool CellPhones::isFinish()
{
	if (m_s1.compare(m_s) != 0)
		return false;

	return true;	    
}

void CellPhones::onPressed(sf::RenderWindow& ,sf::Event &event)
{
	std::string text;
	if (m_isClick)
	{
		text = event.text.unicode;
		if (m_s1.size() < 10 || text == "\b")
		{
			if (text == "\b")
				m_s1.erase(m_s1.size() - 1);
			else
				m_s1 += event.text.unicode;
			m_f.loadFromFile("arial.ttf");
			m_text.setFont(m_f);
			m_text.setString(m_s1);
			m_text.setCharacterSize(21);
			m_text.setPosition(420, 250);
			m_text.setFillColor(sf::Color::White);
			if (m_s1.compare(m_s) == 0)
			{
				m_buffer.loadFromFile("voice.wav");
				m_sound.setBuffer(m_buffer);
				m_sound.play();
			}
		}
	}
}

