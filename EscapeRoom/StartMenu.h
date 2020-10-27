#pragma once
#include "Menu.h"
#include "ActionButton.h"
#include <SFML/Audio.hpp>
class StartMenu :
	public Menu
{
public:
	StartMenu();
	virtual ~StartMenu();

	//StartMenu(sf::RenderWindow& window) { menu(window); }
	virtual void onClick(sf::RenderWindow&, sf::Event& event, Board&, Controller&) override;
	virtual void onOver(sf::RenderWindow&, sf::Event&) override;
	void menu(/*sf::RenderWindow&*/);
	void start(Controller& c);
	void help(sf::RenderWindow& window, sf::Event& event);
	void draw(sf::RenderWindow&) override;
	void transparent(int n);
	
private:	
	sf::Font m_font;
	sf::Text m_text;
	std::vector<sf::Vector2f> m_pos{ 3 };
	std::vector<std::shared_ptr<ActionButton>> m_actionButton;
	sf::RectangleShape m_recbg;
	sf::Texture m_ttbg;
	bool m_boSound[3] = {true ,true ,true};
};

