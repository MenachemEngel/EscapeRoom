#pragma once
#include "Puzzle.h"
class equation :
	public Puzzle
{
public:
	equation();
	void creat(int a[] = { 0 })override;
	void onClick(sf::RenderWindow&) override;
	void draw(sf::RenderWindow&)override;
	bool isFinish()override;
	void check();
	void onPressed(sf::RenderWindow& window, sf::Event& event) override {};
	~equation();
private:

	std::vector<sf::RectangleShape> m_rs{8};
	std::vector<sf::RectangleShape> m_action{4};
	std::vector<sf::RectangleShape> m_temp_action{4};
	std::vector<sf::Texture> m_t{12};
};

