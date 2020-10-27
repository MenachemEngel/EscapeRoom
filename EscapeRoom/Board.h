#pragma once
#include "Object.h"
#include "OpenItem.h"
#include "CaverItem.h"
#include "Screen.h"
#include "PresentButton.h"
#include "Safe.h"
#include "Puzzle.h"
#include <vector>
#include <fstream>
#include <istream>
#include <memory>
#include <string>


class Board :
	public Object
{
public:
	Board();
	virtual ~Board();

	//create board function
	void createBord();
	//create object function
	void createObject(char c ,std::istream& iss ,int i);
	//read line function
	std::string readLine();
	//update file name function
	void updateFileName();
	//draw funcion
	virtual void draw(sf::RenderWindow& window) override;
	//clean board function
	void cleanBoard();
	//get areas acreens function
	std::vector < std::shared_ptr<Screen>> getAreasScreens();
	//get item function
	std::vector < std::vector<std::shared_ptr<Item>>>& getItems();
	//get area function
	std::vector<std::vector<std::shared_ptr<PresentButton>>> getAreas();
	//check screen function
	bool checkScreen(int i);
	//get screen function
	std::shared_ptr<Screen> getScreen();
	//replace screen function
	void repaceScreen(int i);
	//back button function
	sf::Text backButton();
	//set screen function
	void setScreen(std::shared_ptr<Screen>& scr);
	//get level function
	int& getLevel();
	//get  time function
	float getTime();

private:
	std::shared_ptr<Screen> m_scr;
	std::vector<std::shared_ptr<Screen>> m_generalImages;
	std::vector<std::shared_ptr<Screen>> m_areaImages;
	std::vector<std::vector<std::shared_ptr<PresentButton>>> m_areaBottons;
	std::vector<std::vector<std::shared_ptr<Item>>> m_item;
	std::vector<std::shared_ptr<Item>> m_itemLine;
	std::fstream m_file;
	int m_level = 1;
	std::string m_fileName;
	bool insert = false ,nl = false;
	sf::Text m_back;
	Puzzle* m_safe;
	float m_time = 0;
};

