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

	registerAction(sf::Keyboard::Scan::A, "LEFT");
	registerAction(sf::Keyboard::Scan::D, "RIGHT");

	m_playerConfig = { 200, 200, 0, 0, 3.0f, 0, "" };

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
	spawnPlayer();

	auto file = std::ifstream(m_levelPath);
	std::string tileType, aniName, gridXstr, gridYstr;
	while (file >> tileType)
	{
		file >> aniName >> gridXstr >> gridYstr;
		float gridX = std::stof(gridXstr);
		float gridY = std::stof(gridYstr);

		if (tileType == "Tile")
		{
			auto entity = m_entityManager.addEntity(aniName);
			entity->add<CTransform>(gridToMidPixel(gridX, gridY, entity));
			entity->add<CAnimation>(m_game->assets().getAnimation(aniName), false);
		}
		else if (tileType == "Dec")
		{

		}
	}

}

std::shared_ptr<Entity> Scene_Play::player()
{
	auto& player = m_entityManager.getEntities("player");
	assert(player.size() == 1);
	return player.front();
}

void Scene_Play::spawnPlayer()
{
	auto entity = m_entityManager.addEntity("player");
	entity->add<CTransform>(Vec2f(m_playerConfig.X, m_playerConfig.Y));
	entity->add<CAnimation>(m_game->assets().getAnimation("BikerIdle"), true);
}

void Scene_Play::update()
{
	m_entityManager.update();
	sMovement();
	sAnimation();
}

void Scene_Play::sMovement()
{
	for (auto& entity : m_entityManager.getEntities())
	{
		auto& eTransform = entity->get<CTransform>();
		eTransform.pos += eTransform.velocity;
	}
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
	auto& p = player()->get<CTransform>();
	if (action.m_type == "START")
	{
		if (action.m_name == "LEFT")
		{
			p.velocity.x = -m_playerConfig.SPEED;
		}
		else if (action.m_name == "RIGHT")
		{
			p.velocity.x = m_playerConfig.SPEED;
		}
	}
	else if (action.m_type == "END")
	{
		if (action.m_name == "LEFT")
		{
			p.velocity.x = 0;
		}
		if (action.m_name == "RIGHT")
		{
			p.velocity.x = 0;
		}
	}
}

void Scene_Play::sAnimation()
{
	for (auto& entity : m_entityManager.getEntities())
	{
		if (!entity->has<CAnimation>())
			continue;

		auto& eAnimation = entity->get<CAnimation>();
		eAnimation.animation.update();
	}
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