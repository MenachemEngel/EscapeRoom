#pragma once
#include <memory>
#include "Puzzle.h"

class MemoryGame :
	public Puzzle
{
public:
	MemoryGame(){}
	void creat(int a[] = { 0 })override;
	void onClick(sf::RenderWindow&) override;
	void draw(sf::RenderWindow&)override;
	bool isFinish()override;
	void check();
	void onPressed(sf::RenderWindow& window, sf::Event& event) override {};
	~MemoryGame() {}

private:

	std::vector<sf::RectangleShape> m_rs{ 15 };
	std::vector<sf::RectangleShape> m_temp_rs{ 24 };
	std::vector<sf::Texture> m_t{ 15 };
	std::vector<std::shared_ptr<sf::RectangleShape>> m_open{ 2 };
	std::vector<int> m_numbers;
	sf::Clock clock;
	float m_prevTime = 3;
};

