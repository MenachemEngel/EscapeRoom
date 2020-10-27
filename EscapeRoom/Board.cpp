#include "Board.h"
#include "Constants.h"
#include "Controller.h"
//s#include "Safe.h"
#include <sstream>
#include <Windows.h>
#include <iostream>
#include "MemoryGame.h"
#include "BoxShapes.h"
#include "CellPhones.h"
#include "equation.h"
#include "Watch.h"


Board::Board()
{
	m_back.setFont(Controller::m_font);
	m_back.setFillColor(sf::Color::Black);
	m_back.setCharacterSize(WINDOW_SIZE_H / 20);
	m_back.setPosition(0 , WINDOW_SIZE_H - (WINDOW_SIZE_H / 15));
	m_back.setString("Back");
}


Board::~Board()
{
}

void Board::createBord()
{
	updateFileName();
	cleanBoard();
	m_file.open(m_fileName);
	if (m_file.is_open()) {
		for (int i = 0; !m_file.eof(); i++) {
			char c;
			std::istringstream iss;
			iss.str(readLine());
			iss >> c;
			createObject(c ,iss ,i);
		}
		m_file.close();
	}
	m_item.push_back(m_itemLine);
	m_scr = m_generalImages[0];
	m_file.close();
}

std::string Board::readLine()
{
	std::string line;
	if (m_file.is_open() && !m_file.eof()) {
		std::getline(m_file ,line);
	}
	nl = true;
	return line;
}

void Board::updateFileName()
{
	m_fileName = "Level" + std::to_string(m_level) + ".txt";
	m_level++;
}

void Board::draw(sf::RenderWindow & window)
{
	m_scr->draw(window);
	for (int i = 0; i < m_generalImages.size(); i++) {
		if (m_scr->getScreen().compare(m_generalImages[i]->getScreen()) == 0) {
			std::for_each(m_areaBottons[i].begin(), m_areaBottons[i].end(), [&window](auto& drw) {drw->draw(window); });
			return;
		}
	}
	for (int i = 0; i < m_areaImages.size(); i++) {
		if (m_scr->getScreen().compare(m_areaImages[i]->getScreen()) == 0) {
			if (!m_scr->getPswd()) {
				std::for_each(m_item[i + 1].begin(), m_item[i + 1].end(), [&window](auto& drw) {drw->draw(window); });
			}
			window.draw(m_back);
			return;
		}
	}
}

void Board::cleanBoard()
{
	m_generalImages.clear();
	m_areaImages.clear();
	m_areaBottons.clear();
	m_item.clear();
}

std::vector<std::shared_ptr<Screen>> Board::getAreasScreens()
{
	return m_areaImages;
}

std::vector<std::vector<std::shared_ptr<Item>>>& Board::getItems()
{
	return m_item;
}

std::vector<std::vector<std::shared_ptr<PresentButton>>> Board::getAreas()
{
	return m_areaBottons;
}

bool Board::checkScreen(int i)
{
	return m_scr->getScreen().compare(m_generalImages[i]->getScreen()) == 0;
}

std::shared_ptr<Screen> Board::getScreen()
{
	return m_scr;
}

void Board::repaceScreen(int i)
{
	m_scr = m_areaImages[i];
}

sf::Text Board::backButton()
{
	return m_back;
}

void Board::setScreen(std::shared_ptr<Screen>& scr)
{
	m_scr = scr;
}

void Board::createObject(char c, std::istream& iss, int i) {
	std::string fname ,fname2;
	double w, h;
	double a[4];
	int s[4];
	switch (c) {
		case 's': 
			iss >> m_time;
			break;
		case 'g': {
			iss >> fname;
			m_generalImages.emplace_back(std::make_shared<Screen>(fname));
			std::vector<std::shared_ptr<PresentButton>> v;
			while (!iss.eof()) {
				for (int i = 0; i < 4; i++) { iss >> a[i]; }
				v.emplace_back(std::make_shared<PresentButton>(
					sf::Vector2f(WINDOW_SIZE_W / a[0] , WINDOW_SIZE_W / a[1])
					, sf::Vector2f(WINDOW_SIZE_W / a[2] , WINDOW_SIZE_W / a[3])));
			}
			m_areaBottons.emplace_back(v);
		}
			break;
		case 'f': {
			iss >> fname;
			if (!iss.eof()) {
				iss >> fname2;
				if (!iss.eof()) {
					for (int i = 0; i < 4; i++) {
						iss >> s[i];
					}
					m_areaImages.emplace_back(std::make_shared<Screen>(fname, fname2 ,s));
				}
				else {
					m_areaImages.emplace_back(std::make_shared<Screen>(fname, fname2));
				}
			}
			else {
				m_areaImages.emplace_back(std::make_shared<Screen>(fname));
			}
			m_item.push_back(m_itemLine);
			m_itemLine.clear();
		}
			break;
		case 'o':
		case 'c': {
			while (!iss.eof()) {	
				iss >> fname;
				iss >> w >> h;
				if (!iss.eof()) {
					for (int i = 0; i < 4; i++) {
						iss >> s[i];
					}
				}
				switch (c)
				{
					case 'o':
						m_itemLine.emplace_back(std::make_shared<OpenItem>(WINDOW_SIZE_W / w, WINDOW_SIZE_H / h ,fname ,s));
						break;
					case 'c':
						m_itemLine.emplace_back(std::make_shared<CaverItem>(WINDOW_SIZE_W / w , WINDOW_SIZE_H / h, fname ,s));
						break;
				}
				if (!iss.eof()) {
					iss >> c;
				}
			}
			break;
		}
		case 'p':
			for (int i = 0; i < 4; i++) {
				iss >> s[i];
			}
			std::cout << "passwqrd\n";
			m_safe = new Safe();
			m_safe->creat(s);
			m_areaImages[m_areaImages.size() - 1]->setPuzzle(m_safe);
			break;
		case 't':
			iss >> m_time;
			break;
		case 'z':
			m_safe = new MemoryGame();
			m_safe->creat();
			m_areaImages[m_areaImages.size() - 1]->setPuzzle(m_safe);
			break;
		case 'w':
			m_safe = new Watch();
			m_safe->creat();
			m_areaImages[m_areaImages.size() - 1]->setPuzzle(m_safe);
			break;
		case 'e':
			m_safe = new equation();
			m_safe->creat();
			m_areaImages[m_areaImages.size() - 1]->setPuzzle(m_safe);
			break;
		case 'b':
			m_safe = new BoxShapes();
			m_safe->creat();
			m_areaImages[m_areaImages.size() - 1]->setPuzzle(m_safe);
			break;
		case 'x':
			m_safe = new CellPhones(0.1);
			m_safe->creat();
			m_areaImages[m_areaImages.size() - 1]->setPuzzle(m_safe);
			break;
	}
}

int& Board::getLevel() {
	return m_level;
}

float Board::getTime() {
	return m_time;
}