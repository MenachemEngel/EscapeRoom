#pragma once
#include "Puzzle.h"
#include <SFML/Audio.hpp>
class CellPhones :
	public Puzzle
{
public:
	CellPhones(float f) : m_prevTime(f){}
	void creat(int a[] = { 0 })override;
	void onClick(sf::RenderWindow&)override;
	void draw(sf::RenderWindow&)override;
	bool isFinish()override;
	void onPressed(sf::RenderWindow& ,sf::Event&)override;
	bool getIsClick() { return m_isClick; }
	void setClick();
	~CellPhones(){}
private:
	std::vector<sf::RectangleShape> m_rs{4};
	std::vector<sf::RectangleShape> m_temp_rs{4};
	std::vector<sf::Texture> m_t{4};
	sf::Text m_text;
	sf::Font m_f;
	std::string m_s1;
	std::string m_s = {"0544454437"};
	sf::Sound m_sound;
	sf::SoundBuffer m_buffer;
	bool m_isClick;
	sf::Clock clock;
	float m_prevTime;
};

