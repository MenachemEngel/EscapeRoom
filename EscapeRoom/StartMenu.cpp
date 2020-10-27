#include "StartMenu.h"
#include "Constants.h"
#include "Controller.h"

StartMenu::StartMenu()
{
	menu();
}


StartMenu::~StartMenu()
{
}

void StartMenu::onClick(sf::RenderWindow& window, sf::Event& event, Board& board, Controller &c)
{
	sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	if (event.mouseButton.button == sf::Mouse::Left) {
		if (m_actionButton[0]->getRec().getGlobalBounds().contains(v2f)) {
			Controller::m_sound["click"].play();
			start(c);
		}
		if (m_actionButton[1]->getRec().getGlobalBounds().contains(v2f)) {
			Controller::m_sound["click"].play();
			help(window, event);
		}
		if (m_actionButton[2]->getRec().getGlobalBounds().contains(v2f)) {
			Controller::m_sound["click"].play();
			window.close();
		}
	}
}

void StartMenu::onOver(sf::RenderWindow &window, sf::Event &event)
{
	sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	for (int i = 0; i < 3; i++) {
		if (m_actionButton[i]->getRec().getGlobalBounds().contains(v2f)) {
			//m_actionButton[i]->getRec().setOutlineColor(sf::Color::Red);
			m_actionButton[i]->getRec().setFillColor(sf::Color(255 ,255 ,255 ,100));
			transparent(i);
			if (m_boSound[i]) {
				Controller::m_sound["over"].play();
				m_boSound[i] = false;
			}
			return;
		}
	}

	transparent(-1);
	
	draw(window);
}

void StartMenu::menu(/*sf::RenderWindow& window*/)
{
	sf::Vector2f v(WINDOW_SIZE_W / 4, WINDOW_SIZE_H / 6);
	sf::Vector2f pos(WINDOW_SIZE_W / 8, WINDOW_SIZE_H / 2.2);
	m_ttbg.loadFromFile(MENU_ARRAY[0]);
	m_recbg.setTexture(&m_ttbg ,true);
	//m_rectangle[0].setPosition(0, 0);
	m_recbg.setSize(sf::Vector2f(WINDOW_SIZE_W ,WINDOW_SIZE_H));

	for (int i = 0; i < 3; i++)
	{
		m_actionButton.emplace_back(std::make_shared<ActionButton>());
		m_actionButton[i]->setTexture(MENU_ARRAY[i+1]);
		m_actionButton[i]->getRec().setPosition(pos.x, pos.y + (v.y * i));
		m_actionButton[i]->getRec().setSize(v);
		//m_actionButton[i]->getRec().setOutlineThickness(5);
		//m_actionButton[i]->getRec().setOutlineColor(sf::Color::Transparent);
	}
	//draw(window);
}

void StartMenu::start(Controller& c)
{
	c.play();
}

void StartMenu::help(sf::RenderWindow &window ,sf::Event& event)
{
	window.clear();
	sf::RectangleShape rs;
	sf::Texture t;
	sf::Vector2f v1(WINDOW_SIZE_W, WINDOW_SIZE_H);
	t.loadFromFile("background.png");
	rs.setTexture(&t);
	rs.setPosition(0, 0);
	rs.setSize(v1);
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setLineSpacing(1.5);
	m_text.setString(R"(
    You stuck in rooms with evil ghost.
	You have to escape before she catch you.
	Go around the room, pick up stuff 
				and look for clues that will lead you out from the room.
	Warning: It would be really unpleasant if the wind caught you.

	The game created by Menachem Engel and Elchanan Madmon
	)");
	m_text.setCharacterSize(WINDOW_SIZE_W / 50);
	m_text.setFillColor(sf::Color(153 ,0 ,0 ,255));
	sf::Text tcls;
	tcls.setFont(m_font);
	tcls.setString("Back");
	tcls.setFillColor(sf::Color::Black);
	tcls.setCharacterSize(WINDOW_SIZE_W / 50);
	tcls.setPosition(WINDOW_SIZE_W - 200 ,0);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (tcls.getGlobalBounds().contains(v2f)) {
						Controller::m_sound["click"].play();
						return;
					}
				}
			}
			else if (event.type == sf::Event::MouseMoved) {
				sf::Vector2f v2f = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if (tcls.getGlobalBounds().contains(v2f)) {
					tcls.setFillColor(sf::Color(0, 0, 0, 100));
				}
				else {
					tcls.setFillColor(sf::Color::Black);
				}
			}
			else if(event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Up) {
					m_text.setPosition(m_text.getPosition().x , m_text.getPosition().y + 10);
				}
				else if (event.key.code == sf::Keyboard::Down) {
					m_text.setPosition(m_text.getPosition().x, m_text.getPosition().y - 10);
				}
				else if (event.key.code == sf::Keyboard::Escape) {
					return;
				}
			}
		}
	window.draw(rs);
	window.draw(m_text);
	window.draw(tcls);
	window.display();
	}
}

void StartMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_recbg);
	std::for_each(m_actionButton.begin(), m_actionButton.end(), [&window](auto& drw) {drw->draw(window); });
}

void StartMenu::transparent(int n)
{
	for (int i = 0; i < m_actionButton.size(); i++) {
		if (i != n) {
			//m_actionButton[i]->getRec().setOutlineColor(sf::Color::Transparent);
			m_actionButton[i]->getRec().setFillColor(sf::Color(255, 255, 255, 255));
			m_boSound[i] = true;
		}
	}
}

