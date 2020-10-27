#pragma once
#include "Object.h"
#include "Puzzle.h"
#include <string>
#include <vector>

class PlayMenu;

class Screen :
	public Object
{
public:
	//c-tors and d-tors
	Screen();
	Screen(std::string img);
	Screen(std::string img , std::string img2);
	Screen(std::string img , std::string img2 ,int a[]);
	~Screen();
	
	//setScreen function
	void setScreen(std::string str);
	//getScreen function
	std::string getScreen();
	//setSize function
	void setSize(double a ,double b);
	//set puzzle function
	void setPuzzle(Puzzle* s);
	//set pswd function
	void setPswd(bool b);
	//get pswd function
	bool getPswd();
	//on click function
	void onClick(sf::RenderWindow& window ,sf::Event& event, PlayMenu pm);
	//draw function
	void draw(sf::RenderWindow& window) override;
	//replace img function
	void replaceImg();
	//is free function
	bool isfree();
	Puzzle* getPuzl();

private:
	sf::RectangleShape m_rec;
	sf::Texture m_tt;
	std::vector<std::string> m_imgs;
	std::string m_img;
	Puzzle* m_puzzle = nullptr;
	int m_passwd[4];
	bool m_pswd = false ,m_lock = false ,m_initPswd = false;
};

