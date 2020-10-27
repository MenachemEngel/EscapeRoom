#pragma once
#include "Puzzle.h"
class Watch :
	public Puzzle
{
public:
	Watch();
	void creat(int a[] = { 0 })override;
	void onClick(sf::RenderWindow&) override;
	void draw(sf::RenderWindow&)override;
	bool isFinish()override;
	void check();
	void onPressed(sf::RenderWindow& window, sf::Event& event) override {};
	~Watch(){}

private:

	std::vector<sf::RectangleShape> m_rs{13};
	std::vector<sf::Texture> m_t{3};
	float m_f[8] = {0, 45, 90, 135, 180, 225, 270, 315};
};

