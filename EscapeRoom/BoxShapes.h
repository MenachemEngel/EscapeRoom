#pragma once
#include "Puzzle.h"
class BoxShapes :
	public Puzzle
{
public:

	BoxShapes();
	void creat(int a[] = { 0 })override;
	void onClick(sf::RenderWindow&) override;
	void draw(sf::RenderWindow&)override;
	bool isFinish()override;
	void check();
	void onPressed(sf::RenderWindow& window, sf::Event& event) override {};
	~BoxShapes();

private:

	std::vector<sf::RectangleShape> m_rs{14};
	std::vector<sf::RectangleShape> m_temp_rs{10};
	std::vector<sf::Texture> m_t{14};
};

