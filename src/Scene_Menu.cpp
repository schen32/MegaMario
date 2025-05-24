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

	m_levelPaths.push_back("assets/play.txt");

	m_menuText.setFont(m_game->assets().getFont("Pixel"));

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

	m_menuText.setString(m_title);
	m_menuText.setFillColor(sf::Color::White);

	const float posX = window.getSize().x / 2.0f -
		m_menuText.getLocalBounds().size.x / 2.0f;
	const float posY = 10;
	m_menuText.setPosition({ posX, posY });

	window.draw(m_menuText);

	for (int sI = 0; sI < m_menuStrings.size(); sI++)
	{
		const float	posX = 20;
		const float posY = 150 + (float)sI * 100;
		m_menuText.setPosition({ posX, posY });

		if (m_selectedMenuIndex == sI)
		{
			m_menuText.setString(m_menuStrings[sI] + " <-");
			m_menuText.setFillColor(sf::Color::Black);
		}
		else
		{
			m_menuText.setString(m_menuStrings[sI]);
			m_menuText.setFillColor(sf::Color::White);
		}
		window.draw(m_menuText);
	}
	
	sf::Text upText(m_game->assets().getFont("Pixel"), "UP: W", 25);
	upText.setPosition({ 10, (float)window.getSize().y - 100 });
	window.draw(upText);

	sf::Text downText(m_game->assets().getFont("Pixel"), "DOWN: S", 25);
	downText.setPosition({ upText.getPosition().x + upText.getLocalBounds().size.x + 40,
		(float)window.getSize().y - 100});
	window.draw(downText);

	sf::Text playText(m_game->assets().getFont("Pixel"), "PLAY: D", 25);
	playText.setPosition({ downText.getPosition().x + downText.getLocalBounds().size.x + 40,
		(float)window.getSize().y - 100 });
	window.draw(playText);

	sf::Text backText(m_game->assets().getFont("Pixel"), "BACK: ESC", 25);
	backText.setPosition({ playText.getPosition().x + playText.getLocalBounds().size.x + 40,
		(float)window.getSize().y - 100 });
	window.draw(backText);
}