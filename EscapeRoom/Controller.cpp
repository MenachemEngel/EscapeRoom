#include "Controller.h"
#include "Constants.h"
#include <Windows.h>

//static variabls
sf::Font Controller::m_font = sf::Font();
std::map<std::string, sf::Sound> Controller::m_sound = std::map<std::string, sf::Sound>();

Controller::Controller()
{
	m_window.create(sf::VideoMode(WINDOW_SIZE_W , WINDOW_SIZE_H) ,"Escape Room" ,sf::Style::Close);
	m_tBackground.loadFromFile("background.png");
	m_recBackground.setTexture(&m_tBackground ,true);
	m_recBackground.setSize(sf::Vector2f(WINDOW_SIZE_W ,WINDOW_SIZE_H));
	std::cout << WINDOW_SIZE_W << std::endl;
	std::cout << WINDOW_SIZE_H << std::endl;
	m_music[0].openFromFile("menuBackgroundmusic.ogg");
	m_music[1].openFromFile("gameBackgroundmusic.ogg");
	m_ab.setTexture("toMenu.png");
	m_ab.getRec().setSize(sf::Vector2f(PLAY_MENU_SIZE.x, WINDOW_SIZE_H / 20));
	m_ab.getRec().setPosition(WINDOW_SIZE_W - m_ab.getRec().getSize().x - 50, WINDOW_SIZE_H - m_ab.getRec().getSize().y - 20);
	m_font.loadFromFile("arial.ttf");
	loadSound();
	m_tclock.setFont(m_font);
	m_tclock.setFillColor(sf::Color(153, 0, 0, 255));
	m_tclock.setCharacterSize(WINDOW_SIZE_H / 20);
}

Controller::~Controller()
{
}

void Controller::play()
{
	std::shared_ptr<Screen> scr;
	
	m_music[0].stop();
	m_music[1].setLoop(true);
	m_music[1].play();
	while (m_window.isOpen()) {
		if (finish) {
			m_playMenu.clearBag();
			try {
				m_board.createBord();
			}
			catch(std::ios_base::failure){
				throw std::string("Some error occured :(");
			}
			sf::Text ml;
			ml.setFont(m_font);
			ml.setString("Level " + std::to_string(m_board.getLevel()-1));
			ml.setCharacterSize(WINDOW_SIZE_H / 20);
			ml.setPosition(WINDOW_SIZE_W / 2.5 ,WINDOW_SIZE_H / 2.5);
			ml.setFillColor(sf::Color(153 ,0 ,0 ,255));
			m_window.clear();
			m_window.draw(m_recBackground);
			m_window.draw(ml);
			m_window.display();
			Sleep(1500);
			m_clock.restart();
			finish = false;
		}
		m_tclock.setString(std::to_string(int(m_clock.getElapsedTime().asSeconds())) + "/" + std::to_string(int(m_board.getTime())));
		while (m_window.pollEvent(m_event)) {
			if (m_event.type == sf::Event::Closed) {
				m_window.close();
			}
			else if (m_event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f v2f = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				m_playMenu.onClick(m_window, m_event, m_board, *this);
				if (m_ab.getRec().getGlobalBounds().contains(v2f)) {
					m_sound["click"].play();
					m_music[1].stop();
					m_music[0].setLoop(true);
					m_music[0].play();
					m_board.cleanBoard();
					m_playMenu.clearBag();
					m_board.getLevel() = 1;
					return;
				}
				if (m_event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < m_board.getAreas().size(); i++) {
						if (m_board.checkScreen(i)) {
							for (int j = 0; j < m_board.getAreas()[i].size(); j++) {
								if (m_board.getAreas()[i][j]->getRec().getGlobalBounds().contains(v2f)) {
									m_sound["click"].play();
									scr = m_board.getScreen();
									m_board.repaceScreen(j);
									break;
								}
							}
							break;
						}
					}
					for (int i = 0; i < m_board.getAreasScreens().size(); i++) {
						if (m_board.getScreen()->getScreen().compare(m_board.getAreasScreens()[i]->getScreen()) == 0) {
							for (int j = 0; j < m_board.getItems()[i + 1].size(); j++) {
								if (m_board.getItems()[i + 1][j]->getRec().getGlobalBounds().contains(v2f)) {
									m_sound["pick"].play();
									if (m_playMenu.getEmptyItem() != nullptr) {
										m_board.getItems()[i + 1][j]->move(m_playMenu.getEmptyItem()->getRec().getPosition());
									}
									m_playMenu.setItem(m_board.getItems()[i + 1][j]);
									m_board.getItems()[i + 1].erase(m_board.getItems()[i+1].begin()+j);
									break;
								}
							}
							break;
						}
					}
					//if (m_board.getScreen()->getPswd()) {
						m_board.getScreen()->onClick(m_window, m_event ,m_playMenu);
					//}
					if (m_board.backButton().getGlobalBounds().contains(v2f)) {
						m_sound["click"].play();
						m_board.setScreen(scr);
					}
				}
			}
			else if (m_event.type == sf::Event::MouseMoved) {
				m_playMenu.onOver(m_window, m_event);
			}
			else if (m_event.type == sf::Event::KeyPressed) {
				if (m_board.getScreen()->getPuzl()!=nullptr) {
					m_board.getScreen()->getPuzl()->onPressed(m_window, m_event);
				}
			}
		}
		checkIfFinish();
		if (finish) {
			m_playMenu.clearBag();
			if (m_board.getLevel() == NUM_OF_LEVELS+1) {
				finishGame();
				return;
			}
		}
		if (int(m_board.getTime())+1==int(m_clock.getElapsedTime().asSeconds())) {
			failure();
			return;	
		}
		m_window.clear(sf::Color(0, 153, 230, 255));
		m_window.draw(m_recBackground);
		m_board.draw(m_window);
		m_playMenu.draw(m_window);
		m_ab.draw(m_window);
		m_window.draw(m_tclock);
		m_window.display();
	}
}
void Controller::checkIfFinish() {
	for (auto &v : m_board.getAreasScreens()) {
		if (!v->isfree()) {
			return;
		}
	}
	m_sound["win"].play();
	finish = true;
}
void Controller::finishGame() {
	sf::RectangleShape rec;
	rec.setSize(sf::Vector2f(WINDOW_SIZE_W ,WINDOW_SIZE_H));
	sf::Texture tt;
	tt.loadFromFile("win.png");
	rec.setTexture(&tt ,true);
	m_window.clear();
	m_window.draw(m_recBackground);
	m_window.draw(rec);
	m_window.display();
	m_sound["fwin"].play();
	Sleep(5000);
	m_board.getLevel() = 1;
}

void Controller::failure() {
	sf::RectangleShape rec;
	rec.setSize(sf::Vector2f(WINDOW_SIZE_W, WINDOW_SIZE_H));
	sf::Texture tt;
	tt.loadFromFile("failure.jpg");
	rec.setTexture(&tt, true);
	m_window.clear();
	m_window.draw(rec);
	m_window.display();
	m_sound["failure"].play();
	Sleep(5000);
	m_board.getLevel() = 1;
	m_clock.restart();
}

void Controller::run()
{
	m_music[1].stop();
	m_music[0].setLoop(true);
	m_music[0].play();
	while (m_window.isOpen()) {
		while (m_window.pollEvent(m_event)) {
			if (m_event.type == sf::Event::Closed) {
				m_window.close();
			}
			else if (m_event.type == sf::Event::MouseButtonPressed) {
				m_startMenu.onClick(m_window, m_event, m_board, *this);
			}
			else if (m_event.type == sf::Event::MouseMoved) {
				m_startMenu.onOver(m_window, m_event);
			}
		}
		m_window.clear(sf::Color(0, 153, 230, 255));
		m_window.draw(m_recBackground);
		m_startMenu.draw(m_window);
		m_window.display();
	}
}

void Controller::loadSound() {
	
	m_tsb[0].loadFromFile("pick.ogg");
	m_ts.setBuffer(m_tsb[0]);
	m_sound["pick"] = m_ts;
	m_tsb[1].loadFromFile("win.ogg");
	m_ts.setBuffer(m_tsb[1]);
	m_sound["win"] = m_ts;
	m_tsb[2].loadFromFile("failure.ogg");
	m_ts.setBuffer(m_tsb[2]);
	m_sound["failure"] = m_ts;
	m_tsb[3].loadFromFile("over.ogg");
	m_ts.setBuffer(m_tsb[3]);
	m_sound["over"] = m_ts;
	m_tsb[4].loadFromFile("click.ogg");
	m_ts.setBuffer(m_tsb[4]);
	m_sound["click"] = m_ts;
	m_tsb[5].loadFromFile("Win.wav");
	m_ts.setBuffer(m_tsb[5]);
	m_sound["fwin"] = m_ts;

}


