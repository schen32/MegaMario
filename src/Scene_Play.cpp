#include "Scene_Play.h"
#include "Scene_Menu.h"
#include "Physics.hpp"
#include "Assets.hpp"
#include "GameEngine.h"
#include "Components.hpp"
#include "Action.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>

Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine)
	, m_levelPath(levelPath)
{
	init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
	registerAction(sf::Keyboard::Scan::P, "PAUSE");
	registerAction(sf::Keyboard::Scan::Escape, "QUIT");
	registerAction(sf::Keyboard::Scan::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::Scan::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::Scan::G, "TOGGLE_GRID");

	m_gridText.setCharacterSize(40);
	m_gridText.setFont(m_game->assets().getFont("Pixel"));
	m_gridText.setString("Lets Play");

	loadLevel(levelPath);
}

Vec2f Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	return Vec2f(0, 0);
}

void Scene_Play::loadLevel(const std::string& filename)
{
	auto entity = m_entityManager.addEntity("coin");
	entity->add<CTransform>(Vec2f(200, 200));

	auto& coinAnimation = m_game->assets().getAnimation("AniCoin");
	entity->add<CAnimation>(coinAnimation, true);
}

std::shared_ptr<Entity> Scene_Play::player()
{
	auto& player = m_entityManager.getEntities("player");
	assert(player.size() == 1);
	return player.front();
}

void Scene_Play::spawnPlayer()
{

}

void Scene_Play::update()
{
	m_entityManager.update();
}

void Scene_Play::sMovement()
{

}

void Scene_Play::sAI()
{

}

void Scene_Play::sStatus()
{

}

void Scene_Play::sCollision()
{

}

void Scene_Play::sDoAction(const Action& action)
{

}

void Scene_Play::sAnimation()
{

}

void Scene_Play::sCamera()
{

}

void Scene_Play::onEnd()
{

}

void Scene_Play::sGui()
{

}

void Scene_Play::sRender()
{
	auto& window = m_game->window();
	window.clear();

	for (auto& entity : m_entityManager.getEntities())
	{
		auto& transform = entity->get<CTransform>();
		auto& sprite = entity->get<CAnimation>().animation.m_sprite;

		sprite.setPosition(transform.pos);
		window.draw(sprite);
	}
}