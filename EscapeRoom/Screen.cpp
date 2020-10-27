#include "Screen.h"
#include "Constants.h"
#include "Controller.h"
#include <iostream>

Screen::Screen()
{
	//m_rec.setTexture(&m_tt, true);
	m_rec.setSize(BOARD_SIZE);
}

Screen::Screen(std::string img)
{
	setScreen(img);
	m_rec.setSize(BOARD_SIZE);
	m_imgs.push_back(img);
}

Screen::Screen(std::string img, std::string img2)
{
	setScreen(img);
	m_rec.setSize(BOARD_SIZE);
	m_imgs.push_back(img);
	m_imgs.push_back(img2);
}

Screen::Screen(std::string img, std::string img2 ,int a[])
{
	setScreen(img);
	m_rec.setSize(BOARD_SIZE);
	m_imgs.push_back(img);
	m_imgs.push_back(img2);
	for (int i = 0; i < 4; i++) {
		m_passwd[i] = a[i];
	}
	m_initPswd = true;
}

Screen::~Screen()
{	
}

void Screen::setScreen(std::string str)
{
	m_tt.loadFromFile(str);
	m_img = str;
	m_rec.setTexture(&m_tt ,true);
}

std::string Screen::getScreen()
{
	return m_img;
}

void Screen::setSize(double a, double b)
{
	m_rec.setSize(sf::Vector2f(a, b));
}

void Screen::setPuzzle(Puzzle* s)
{
	m_puzzle = s;
	m_pswd = true;
}

void Screen::setPswd(bool b)
{
	m_pswd = b;
}

bool Screen::getPswd()
{
	return m_pswd;
}

void Screen::onClick(sf::RenderWindow & window, sf::Event & event ,PlayMenu pm)
{
	sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	Controller::m_sound["click"].play();
	if (m_pswd) {
		m_puzzle->onClick(window);
		if (m_puzzle->isFinish()) {
			m_pswd = false;
			m_lock = false;
		}
	}
	else if (m_rec.getGlobalBounds().contains(v2f)) {
		if (m_initPswd){
			try {
				if (pm.getItem() == nullptr) {
					return;
				}else if (pm.getItem()->checkCode(m_passwd)) {
					replaceImg();
					m_initPswd = false;
				}
			}
			catch (std::string str) {
				std::cout << str << std::endl;
			}
		}
		else {
			replaceImg();
		}
	}
}

void Screen::draw(sf::RenderWindow & window)
{
	window.draw(m_rec);
	if (m_pswd) {
		m_puzzle->draw(window);
	}
}

bool Screen::isfree() {
	return !m_pswd && !m_lock && !m_initPswd;
}

void Screen::replaceImg() {
	if (m_imgs.size() == 2 ) {
		if (!m_pswd && !m_lock) {
			if (m_img.compare(m_imgs[0]) == 0) {
				setScreen(m_imgs[1]);
			}
			else {
				setScreen(m_imgs[0]);
			}
		}
	}
}

Puzzle* Screen::getPuzl() {
	return m_puzzle;
}
