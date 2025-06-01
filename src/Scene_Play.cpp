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

	m_playerConfig = { 200, 200, 0, 0, 5.0f, 0, "" };

	m_gridText.setCharacterSize(40);
	m_gridText.setFont(m_game->assets().getFont("Pixel"));
	m_gridText.setString("Lets Play");

	loadLevel(levelPath);
}

Vec2f Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	auto& eAnimation = entity->get<CAnimation>();
	Vec2f eAniSize = eAnimation.animation.m_size;
	
	return Vec2f
	(
		gridX * eAniSize.x + eAniSize.x / 2,
		height() - gridY * eAniSize.y - eAniSize.y / 2
	);
}

void Scene_Play::loadLevel(const std::string& filename)
{
	m_entityManager = EntityManager();
	spawnPlayer();

	std::ifstream file(m_levelPath);
	std::string tileType;
	while (file >> tileType)
	{
		std::string aniName, gridXstr, gridYstr;
		file >> aniName >> gridXstr >> gridYstr;
		float gridX = std::stof(gridXstr);
		float gridY = std::stof(gridYstr);

		if (tileType == "Tile")
		{
			auto entity = m_entityManager.addEntity("Tile");
			auto& eAnimation = entity->add<CAnimation>(m_game->assets().getAnimation(aniName), true);
			entity->add<CTransform>(gridToMidPixel(gridX, gridY, entity));
			entity->add<CBoundingBox>(eAnimation.animation.m_size);
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
	auto& eAnimation = entity->add<CAnimation>(m_game->assets().getAnimation("BikerIdle"), true);
	entity->add<CInput>();
	entity->add<CGravity>(0.0981f);
	entity->add<CBoundingBox>(eAnimation.animation.m_size);
}

void Scene_Play::update()
{
	m_entityManager.update();
	sAnimation();
	sCollision();
	sMovement();
}

void Scene_Play::sMovement()
{
	auto& pInput = player()->get<CInput>();
	auto& pTransform = player()->get<CTransform>();

	pTransform.velocity.x = 0;
	if (pInput.left)
		pTransform.velocity.x -= m_playerConfig.SPEED;
	if (pInput.right)
		pTransform.velocity.x += m_playerConfig.SPEED;

	for (auto& entity : m_entityManager.getEntities())
	{
		auto& eTransform = entity->get<CTransform>();

		if (entity->has<CGravity>())
		{
			auto& eGravity = entity->get<CGravity>();
			eTransform.velocity.y += eGravity.gravity;
		}

		eTransform.prevPos = eTransform.pos;
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
	for (auto& tile : m_entityManager.getEntities("Tile"))
	{
		if (player()->id() == tile->id())
			continue;

		Vec2f overlap = Physics::GetOverlap(player(), tile);
		if (overlap.x > 0 && overlap.y > 0)
		{
			Vec2f prevOverlap = Physics::GetPreviousOverlap(player(), tile);
			auto& pTransform = player()->get<CTransform>();
			
			if (prevOverlap.y > 0)
			{
				pTransform.velocity.x = 0;
				pTransform.pos.x += overlap.x;
			}
			if (prevOverlap.x > 0)
			{
				pTransform.velocity.y = 0;
				pTransform.pos.y -= overlap.y;
			}
		}

	}

}

void Scene_Play::sDoAction(const Action& action)
{
	auto& pInput = player()->get<CInput>();
	if (action.m_type == "START")
	{
		if (action.m_name == "LEFT")
		{
			pInput.left = true;
		}
		else if (action.m_name == "RIGHT")
		{
			pInput.right = true;
		}
	}
	else if (action.m_type == "END")
	{
		if (action.m_name == "LEFT")
		{
			pInput.left = false;
		}
		if (action.m_name == "RIGHT")
		{
			pInput.right = false;
		}
	}
}

void Scene_Play::sAnimation()
{
	auto& pInput = player()->get<CInput>();
	auto& pAnimation = player()->get<CAnimation>();

	if (pInput.left)
		pAnimation.animation.m_sprite.setScale({ -1, 1 });
	if (pInput.right)
		pAnimation.animation.m_sprite.setScale({ 1, 1 });

	for (auto& entity : m_entityManager.getEntities())
	{
		if (!entity->has<CAnimation>())
			continue;

		auto& eAnimation = entity->get<CAnimation>();
		eAnimation.animation.update();
		if (!eAnimation.repeat && eAnimation.animation.hasEnded())
			entity->destroy();
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