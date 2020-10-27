#include "PlayMenu.h"
#include "Constants.h"
#include <algorithm>
#include <iostream>

PlayMenu::PlayMenu()
{
	menu();
}

PlayMenu::PlayMenu(sf::RenderWindow& window)
{
	//menu();
}


PlayMenu::~PlayMenu()
{
}

void PlayMenu::onClick(sf::RenderWindow &window, sf::Event &event, Board &board, Controller &c)
{
	sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	
	for (int i = 0; i < 6; i++) {
		if (m_vp[i]) {
			std::cout << "1" << std::endl;
		}
		else {
			std::cout << "0" << std::endl;
		}
	}
	sf::RectangleShape r(sf::Vector2f(PLAY_MENU_SIZE.x ,WINDOW_SIZE_H));
	r.setPosition(sf::Vector2f(PLAY_MENU_POS.x ,0));
	if (event.mouseButton.button == sf::Mouse::Left) {
		for (int i = 0; i < m_pair.size(); i++) {
			sf::Vector2f pos = m_pair[i].first->getRec().getPosition();
			sf::Vector2f size = m_pair[i].first->getRec().getSize();
			if (!m_vp[i] && m_pair[i].first->getRec().getGlobalBounds().contains(v2f)) {
				m_pair[i].first->getRec().setScale(sf::Vector2f(1.1, 1.1));
				m_pair[i].first->getRec().setPosition(pos.x - size.x / 9, pos.y - size.y / 9);
				m_vp[i] = true;
			}
			else if (r.getGlobalBounds().contains(v2f)){
				if (m_pair[i].first->getRec().getScale() == sf::Vector2f(1.1, 1.1)) {
					m_pair[i].first->getRec().setScale(sf::Vector2f(1, 1));
					m_pair[i].first->getRec().setPosition(pos.x + size.x / 9, pos.y + size.y / 9);
					m_vp[i] = false;
				}
			}
		}
	}

}

void PlayMenu::onOver(sf::RenderWindow& window, sf::Event& event)
{
	sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	for (int i = 0; i < m_pair.size(); i++) {
		if (m_pair[i].first->getRec().getGlobalBounds().contains(v2f)) {
			m_pair[i].first->getRec().setOutlineColor(sf::Color::Red);
			transparent(i);
			draw(window);
			return;
		}
	}

	transparent(-1);
	draw(window);
}

void PlayMenu::menu()
{
	for (int i = 0; i < 6; i++)
	{
		m_pair.emplace_back(std::make_pair(std::make_shared<PresentButton>() , nullptr));
		m_pair[i].first->setTexture("bag.png");
		m_pair[i].first->getRec().setPosition(PLAY_MENU_POS.x, PLAY_MENU_POS.y + ((PLAY_MENU_POS.x/8) * 1.05 * i));
		m_pair[i].first->getRec().setSize(PLAY_MENU_SIZE);
		m_pair[i].first->getRec().setFillColor(sf::Color::White);
		m_pair[i].first->getRec().setOutlineThickness(5);
		m_pair[i].first->getRec().setOutlineColor(sf::Color::Transparent);
	}
}

void PlayMenu::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < m_pair.size(); i++) {
		m_pair[i].first->draw(window);
		if (m_pair[i].second) {
			m_pair[i].second->draw(window);
		}
	}
}

void PlayMenu::transparent(int n)
{
	for (int i = 0; i < m_pair.size(); i++) {
		if (i != n) {
			m_pair[i].first->getRec().setOutlineColor(sf::Color::Transparent);
		}
	}
}

void PlayMenu::setItem(std::shared_ptr<Item>& item)
{
	for (int i = 0; i < m_pair.size(); i++) {
		if (m_pair[i].second == nullptr) {
			m_pair[i].second = item;
			m_pair[i].second->getRec().setPosition(m_pair[i].first->getRec().getPosition());
			break;
		}
	}
}

std::shared_ptr<Item> PlayMenu::getItem()
{
	for (int i = 0; i < 6; i++) {
		if (m_vp[i]) {
			return m_pair[i].second;
		}
	}
	return nullptr;
}

std::shared_ptr<PresentButton> PlayMenu::getEmptyItem()
{
	for (int i = 0; i < 6; i++) {
		if (m_pair[i].second) {
			return m_pair[i].first;
		}
	}
	return nullptr;
}

void PlayMenu::deleteItem(int i)
{
	m_pair[i].second = nullptr;
}

void PlayMenu::clearBag() {
	for (int i = 0; i < m_pair.size(); i++) {
		deleteItem(i);
	}
}