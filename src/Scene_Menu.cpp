#include "Scene_Menu.h"
#include "Assets.hpp"
#include "GameEngine.h"
#include "Components.hpp"
#include "Action.hpp"

#include <iostream>

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Menu::init()
{
	m_title = "MegaMario";
	m_menuStrings.push_back("Start");
	m_menuStrings.push_back("Options");

	m_levelPaths.push_back("map_home.txt");

	m_menuText.setFont(m_game->assets().getFont("PixelOperator8"));
}

void Scene_Menu::update()
{
	sRender();
}

void Scene_Menu::onEnd()
{

}

void Scene_Menu::sDoAction(const Action& action)
{

}

void Scene_Menu::sRender()
{
	auto& window = m_game->window();
	window.clear(sf::Color::Blue);
	window.display();
}