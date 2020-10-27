#include "equation.h"
#include "Constants.h"



equation::equation()
{
	
}

void equation::creat(int a[])
{
	sf::Vector2f v(70.f, 40.f);
	sf::Vector2f pos(0, 150);
	sf::Vector2f v1(sf::VideoMode::getDesktopMode().width / 1.4, sf::VideoMode::getDesktopMode().height / 1.4);
	m_t[0].loadFromFile(EQUATION[0]);
	m_rs[0].setTexture(&m_t[0]);
	m_rs[0].setPosition(0, 0);
	m_rs[0].setSize(v1);

	for (int i = 1; i < 8; i++)
	{
		m_t[i].loadFromFile(EQUATION[i]);
		m_rs[i].setTexture(&m_t[i]);
		m_rs[i].setPosition(pos.x + (130 * i) -60, pos.y);
		m_rs[i].setSize(v);
	}
	sf::Vector2f v3(40.f, 40.f);
	sf::Vector2f pos1(200.f, 40.f);
	for (int i = 0, j=8; i < 4; i++,j++)
	{
		m_t[j].loadFromFile(FOUR_ACTION[i]);
		m_action[i].setTexture(&m_t[j]);
		m_action[i].setSize(v3);
	}
	m_temp_action = m_action;
	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
			m_temp_action[i].setPosition(m_rs[i + 1].getPosition().x + 80, 150);
		else
			m_temp_action[i].setPosition(m_rs[i + 3].getPosition().x + 80, 150);
		m_temp_action[i].setTexture(m_action[2].getTexture());
	}	
}


void equation::onClick(sf::RenderWindow &window)
{
	for (int i =0; i < 4; i++)
	{
		if (m_temp_action[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			for (int j = 0; j < 4; j++)
				if (m_temp_action[i].getTexture() == m_action[j].getTexture())
				{
					if (j != 3)
						m_temp_action[i].setTexture(m_action[j + 1].getTexture());
					else
						m_temp_action[i].setTexture(m_action[0].getTexture());;
					break;
				}
		}
	}
	draw(window);		
}

void equation::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 8; i++)
		window.draw(m_rs[i]);
	for (int i = 0; i < 4; i++)
		window.draw(m_temp_action[i]);
}

bool equation::isFinish()
{
	if (m_temp_action[0].getTexture() == m_action[0].getTexture() &&
		m_temp_action[1].getTexture() == m_action[1].getTexture() &&
		m_temp_action[2].getTexture() == m_action[0].getTexture() &&
		m_temp_action[3].getTexture() == m_action[3].getTexture())
		return true;
	return false;
}

equation::~equation()
{
}
