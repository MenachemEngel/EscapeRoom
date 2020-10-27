#include "Button.h"


Button::Button()
{
}

Button::Button(sf::Vector2f size, sf::Vector2f pos)
{
	m_rec.setSize(size);
	m_rec.setPosition(pos);
	m_rec.setFillColor(sf::Color::Transparent);
}

sf::RectangleShape& Button::getRec() {
	return m_rec;
}

Button::~Button()
{
}

void Button::draw(sf::RenderWindow & window)
{
	window.draw(m_rec);
}

void Button::setTexture(std::string img) {
	m_tt.loadFromFile(img);
	m_rec.setTexture(&m_tt, true);
}
