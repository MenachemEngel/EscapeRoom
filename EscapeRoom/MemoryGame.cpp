#include "MemoryGame.h"
#include "Constants.h"
#include <time.h>



void MemoryGame::creat(int a[])
{
	srand(time(NULL));
	sf::Vector2f v(30.f, 30.f);
	sf::Vector2f pos(0, 150);
	sf::Vector2f v1(sf::VideoMode::getDesktopMode().width / 1.4, sf::VideoMode::getDesktopMode().height / 1.4);
	m_t[0].loadFromFile(MEMORYGAME2[0]);
	m_rs[0].setTexture(&m_t[0]);
	m_rs[0].setPosition(0, 0);
	m_rs[0].setSize(v1);
	
	for (int i = 1; i < 15; i++)
	{
		m_t[i].loadFromFile(MEMORYGAME2[i]);
		m_rs[i].setTexture(&m_t[i]);
		m_rs[i].setSize(v);
	}

	int random;
	std::vector<int> temp(24, 0);
	for (int i = 0; i < 24; i++)
	{
		do
			random = rand() % (13 - 2 + 1) + 2;
		while (temp[random] >= 2);
		temp[random]++;
		m_numbers.push_back(random);
	}

	int k = 0;
	for (int i = 200; i <= 700; i += 100)
	{
		for (int j = 100; j <= 400; j += 100)
		{
			m_temp_rs[k] = m_rs[1];
			m_temp_rs[k].setPosition(i, j);
			k++;
		}
	}

	for (int i = 0; i < 2; i++)
		m_open[i] = NULL;
}

void MemoryGame::onClick(sf::RenderWindow &window)
{
	for (int i = 0; i < m_temp_rs.size(); i++)
	{
		if (m_temp_rs[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			if (m_temp_rs[i].getTexture() == m_rs[1].getTexture())
			{
				if (m_open[0] == NULL || m_open[1] == NULL)
				{
					m_temp_rs[i].setTexture(m_rs[m_numbers[i]].getTexture());
					if (m_open[0] == NULL)
						m_open[0] = std::make_shared<sf::RectangleShape>(m_temp_rs[i]);
					else if (m_open[1] == NULL)
						m_open[1] = std::make_shared<sf::RectangleShape>(m_temp_rs[i]);
				}
			}
			break;
		}
	}
}

void MemoryGame::check()
{
	if (m_open[0] != NULL && m_open[1] != NULL)
	{
		if (m_open[0]->getTexture() == m_open[1]->getTexture())
		{
			for (int i = 0; i < m_temp_rs.size(); i++)
				if (m_temp_rs[i].getTexture() == m_open[0]->getTexture())
					m_temp_rs[i].setTexture(m_rs[14].getTexture());
		}
		else
		{
			for (int i = 0; i < m_temp_rs.size(); i++)
			{
				if (m_temp_rs[i].getTexture() == m_open[0]->getTexture())
					m_temp_rs[i].setTexture(m_rs[1].getTexture());
				else if (m_temp_rs[i].getTexture() == m_open[1]->getTexture())
					m_temp_rs[i].setTexture(m_rs[1].getTexture());
			}
		}
		for (int i = 0; i < m_open.size(); i++)
			m_open[i] = NULL;
	}
}

bool MemoryGame::isFinish()
{
	for (int i = 0; i < m_temp_rs.size(); i++)
		if (m_temp_rs[i].getTexture() != m_rs[14].getTexture())
			return false;
	return true;
}

void MemoryGame::draw(sf::RenderWindow &window)
{
	window.draw(m_rs[0]);
	for (int i = 0; i < m_temp_rs.size(); i++)
		window.draw(m_temp_rs[i]);
	if (clock.getElapsedTime().asSeconds() - m_prevTime > 2)
	{
		m_prevTime = clock.getElapsedTime().asSeconds();
		check();
	}
}
