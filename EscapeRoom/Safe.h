#pragma once
#include "Object.h"
#include "Puzzle.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Safe :
	public Puzzle
{
public:
	Safe();
	~Safe();

	virtual void onClick(sf::RenderWindow& window) override;
	std::vector<sf::RectangleShape> getRecs() const;
	void creat(int a[] = {0})override;
	void loadPasswd();
	virtual void draw(sf::RenderWindow& window) override;
	void incNum(int i);
	
	virtual void onPressed(sf::RenderWindow& window, sf::Event& event) override;
	virtual bool isFinish() override;
private:
	int m_passwd[4];
	int m_sPasswd[4] = { 0 };

	std::vector<sf::RectangleShape> m_rec{ 4 };
	std::vector<sf::Texture> m_tt{ 4 };
};

