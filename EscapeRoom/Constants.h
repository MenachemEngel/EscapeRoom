#pragma once
#include <SFML/Graphics.hpp>

const int WINDOW_SIZE_H = sf::VideoMode::getDesktopMode().height / 1.4;
const int WINDOW_SIZE_W = sf::VideoMode::getDesktopMode().width / 1.4;

const std::string MENU_ARRAY[] = { "start_pic.png","play_button.png","help_button.png","exit_button.png" };

const sf::Vector2f PLAY_MENU_SIZE(WINDOW_SIZE_W/8, WINDOW_SIZE_H/6);
const sf::Vector2f PLAY_MENU_POS(WINDOW_SIZE_W - PLAY_MENU_SIZE.x - PLAY_MENU_SIZE.x / 8, PLAY_MENU_SIZE.y/6);

const sf::Vector2f BOARD_SIZE(WINDOW_SIZE_W - PLAY_MENU_SIZE.x - 50, WINDOW_SIZE_H);

const int NUM_OF_LEVELS = 3;


const std::string CELLPHONES[] = { "background.png","puzl//Phone.png","puzl//Phone1.png", "puzl//13mg.png" };
const std::string WATCH[] = { "background.png","puzl//clock1.png","puzl//arrow.png" };
const std::string MEMORYGAME2[] = { "background.png","puzl//0mg.jpg","puzl//1mg.png","puzl//2mg.png","puzl//3mg.jpg" ,"puzl//4mg.png" ,"puzl//5mg.png", "puzl//6mg.jpg", "puzl//7mg.jpg", "puzl//8mg.jpg", "puzl//9mg.jpg", "puzl//10mg.jpg", "puzl//11mg.png", "puzl//12mg.png", "puzl//13mg.png" };
const std::string BOXSHAPES[] = { "background.png","puzl//r.png","puzl//c.png","puzl//t.png","puzl//x1.png" };
const std::string SHAPES[] = { "puzl//b1.png","puzl//b2.png","puzl//b3.png","puzl//b4.png" };
const std::string EQUATION[] = { "background.png","puzl//e8.png","puzl//e4.png","puzl//e6.png","puzl//e.png","puzl//e66.png","puzl//e77.png" ,"puzl//e44.png" };
const std::string FOUR_ACTION[] = { "puzl//x.png","puzl//+.png","puzl//%.png","puzl//-.png" };