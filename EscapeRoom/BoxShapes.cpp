#include "BoxShapes.h"
#include "Constants.h"


BoxShapes::BoxShapes()
{
}

void BoxShapes::creat(int a[])
{
	sf::Vector2f v(30.f, 30.f);
	sf::Vector2f pos(0, 150);
	sf::Vector2f v1(sf::VideoMode::getDesktopMode().width / 1.4, sf::VideoMode::getDesktopMode().height / 1.4);
	m_t[0].loadFromFile(BOXSHAPES[0]);
	m_rs[0].setTexture(&m_t[0]);
	m_rs[0].setPosition(0, 0);
	m_rs[0].setSize(v1);

	for (int i = 1; i < 5; i++)
	{
		m_t[i].loadFromFile(BOXSHAPES[i]);
		m_rs[i].setTexture(&m_t[i]);
		m_rs[i].setSize(v);
	}

	for (int i = 0; i < 9; i++)
		m_temp_rs[i] = m_rs[1];

	int k = 0;
	for (int i = 400; i < 580; i += 60)
		for (int j = 200; j < 380; j += 60)
			m_temp_rs[k++].setPosition(i, j);

	for (int i = 5, j=0; i < 9; i++, j++)
	{
		m_t[i].loadFromFile(SHAPES[j]);
		m_rs[i].setTexture(&m_t[i]);
		m_rs[i].setSize(sf::Vector2f(150.f, 150.f));
		if (j == 0)
			m_rs[i].setPosition(30, 30);
		if (j == 1)
			m_rs[i].setPosition(800, 30);
		if (j == 2)
			m_rs[i].setPosition(30, 370);
		if (j == 3)
			m_rs[i].setPosition(800, 370);
	}
}


void BoxShapes::onClick(sf::RenderWindow &window)
{
	for (int i = 0; i < 9; i++)
	{
		if (m_temp_rs[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			for (int j = 1; j < 5; j++)
				if (m_temp_rs[i].getTexture() == m_rs[j].getTexture())
				{
					if (j != 4)
						m_temp_rs[i].setTexture(m_rs[j + 1].getTexture());
					else
						m_temp_rs[i].setTexture(m_rs[1].getTexture());;
					break;
				}
		}
	}
	draw(window);
}

void BoxShapes::draw(sf::RenderWindow &window)
{
	window.draw(m_rs[0]);
	for (int i = 0; i < 9; i++)
		window.draw(m_temp_rs[i]);
	for (int i = 5; i < 9; i++)
		window.draw(m_rs[i]);
}

bool BoxShapes::isFinish()
{
	if (m_temp_rs[0].getTexture() == m_rs[4].getTexture() &&
		m_temp_rs[1].getTexture() == m_rs[2].getTexture() &&
		m_temp_rs[2].getTexture() == m_rs[3].getTexture() &&
		m_temp_rs[3].getTexture() == m_rs[3].getTexture() &&
		m_temp_rs[4].getTexture() == m_rs[3].getTexture() &&
		m_temp_rs[5].getTexture() == m_rs[1].getTexture() &&
		m_temp_rs[6].getTexture() == m_rs[1].getTexture() &&
		m_temp_rs[7].getTexture() == m_rs[4].getTexture() &&
		m_temp_rs[8].getTexture() == m_rs[2].getTexture())
		return true;
	return false;
}


BoxShapes::~BoxShapes()
{
}
