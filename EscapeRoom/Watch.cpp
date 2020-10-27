#include "Watch.h"
#include "Constants.h"



Watch::Watch()
{
}

void Watch::creat(int a[])
{
	sf::Vector2f v(200.f, 200.f);
	sf::Vector2f pos(0, 150);
	sf::Vector2f v1(sf::VideoMode::getDesktopMode().width / 1.4, sf::VideoMode::getDesktopMode().height / 1.4);
	
	for (int i = 0; i < 3; i++)
		m_t[i].loadFromFile(WATCH[i]);

	m_rs[0].setTexture(&m_t[0]);
	m_rs[0].setPosition(0, 0);
	m_rs[0].setSize(v1);


	for (int i = 1; i < 7; i++)
	{
		m_rs[i].setTexture(&m_t[1]);
		m_rs[i].setSize(v);
		m_rs[i].setOrigin(15, 15);
	}
	int k = 1;
	for (int i = 100; i < 800; i += 300)
		for (int j = 50; j < 360; j += 280)
			m_rs[k++].setPosition(i, j);

	
	for (int i = 7; i < 13; i++)
	{
		m_rs[i].setTexture(&m_t[2]);
		m_rs[i].setSize(sf::Vector2f(40.f, 40.f));
		m_rs[i].setOrigin(20.f, 20.f);

	}
	for (int i = 185; i < 900; i += 300)
		for (int j = 135; j < 420; j += 280)
			m_rs[k++].setPosition(i, j);
}

void Watch::onClick(sf::RenderWindow &window)
{	
	for (int i = 7; i < 13; i++)
		if (m_rs[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			m_rs[i].rotate(315.f);
			break;
		}
}

void Watch::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 13; i++)
		window.draw(m_rs[i]);
}


bool Watch::isFinish()
{
	if ((m_rs[7].getRotation() == 360 - 315) &&
		(m_rs[8].getRotation() == 360 - 270) &&
		(m_rs[9].getRotation() == 360 - 270) &&
		(m_rs[9].getRotation() == 360 - 270) &&
		(m_rs[10].getRotation() == 360 - 90) &&
		(m_rs[11].getRotation() == 360 - 45) &&
		(m_rs[12].getRotation() == 360 - 135))
		return true;
	return false;
}