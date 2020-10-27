#pragma once
#include "Menu.h"
#include "Item.h"
#include <memory>
#include <map>
#include <utility>

class PlayMenu :
	public Menu
{
public:
	//c-tor and d-tor
	PlayMenu();
	PlayMenu(sf::RenderWindow& window);
	virtual ~PlayMenu();

	virtual void onClick(sf::RenderWindow& window, sf::Event& event, Board& board, Controller& ctrl)override;
	virtual void onOver(sf::RenderWindow& window, sf::Event& event);
	void menu();
	virtual void draw(sf::RenderWindow& window)override;
	void transparent(int n);
	void setItem(std::shared_ptr<Item>& item);
	std::shared_ptr<Item> getItem();
	std::shared_ptr<PresentButton> getEmptyItem();
	void deleteItem(int i);
	void clearBag();

private:
	std::vector<std::pair<std::shared_ptr<PresentButton>, std::shared_ptr<Item>>> m_pair;
	bool m_vp[6] = {false};
};

