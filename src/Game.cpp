#include "Game.h"

#include <iostream>
#include <random>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	m_window.create(sf::VideoMode({ 1280, 720 }), "Mega Mario");
	m_window.setFramerateLimit(60);

	ImGui::SFML::Init(m_window);

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	// int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S
	m_playerConfig = { 32, 32, 100, 100, 100, 250, 250, 250, 4, 6, 5.0f };
	// int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S
	m_bulletConfig = { 6, 6, 250, 250, 250, 250, 250, 250, 2, 12, 100, 15.0f };
	// int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX
	m_enemyConfig = { 40, 40, 250, 10, 10, 3, 3, 7, 60, 120, 2.0f, 6.0f };

	spawnPlayer();
}

std::shared_ptr<Entity> Game::player()
{
	auto& player = m_entities.getEntities("player");
	assert(player.size() == 1);
	return player.front();
}

void Game::run()
{
	while (m_running)
	{
		m_entities.update();

		ImGui::SFML::Update(m_window, m_deltaClock.restart());

		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sLifespan();
			sCollision();
		}
		sUserInput();
		sGUI();
		sRender();

		m_currentFrame++;
	}
	m_window.close();
}

void Game::spawnPlayer()
{
	auto player = m_entities.addEntity("player");

	player->add<CTransform>(Vec2f(m_window.getSize()) / 2,
		Vec2f(0.0f, 0.0f), 0.0f);
	player->add<CInput>();
}

void Game::spawnEnemy()
{

}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{

}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f& target)
{

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2f& target)
{

}

void Game::sMovement()
{
	auto& playerTransform = player()->get<CTransform>();
	auto& playerInput = player()->get<CInput>();

	playerTransform.velocity = { 0.0, 0.0 };
	if (playerInput.up) playerTransform.velocity.y -= m_playerConfig.S;
	if (playerInput.left) playerTransform.velocity.x -= m_playerConfig.S;
	if (playerInput.down) playerTransform.velocity.y += m_playerConfig.S;
	if (playerInput.right) playerTransform.velocity.x += m_playerConfig.S;

	if (playerTransform.velocity.x != 0 && playerTransform.velocity.y != 0) {
		float length = playerTransform.velocity.length();
		playerTransform.velocity = (playerTransform.velocity / length) * m_playerConfig.S;
	}

	for (auto& entity : m_entities.getEntities())
	{
		auto& entityTransform = entity->get<CTransform>();
		entityTransform.pos += entityTransform.velocity;
	}
}

void Game::sLifespan()
{

}

void Game::sCollision()
{

}

void Game::sEnemySpawner()
{
}

void Game::sGUI()
{
	ImGui::Begin("Geometry Wars");

	ImGui::End();
}

void Game::sRender()
{
	m_window.clear();

	for (auto& entity : m_entities.getEntities())
	{
		auto& entityTransform = entity->get<CTransform>();

		auto shape = sf::CircleShape(50.0f);
		shape.setPosition(entityTransform.pos);

		m_window.draw(shape);
	}
	m_window.draw(m_text);

	ImGui::SFML::Render(m_window);

	m_window.display();
}

void Game::sUserInput()
{
	while (const std::optional event = m_window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(m_window, *event);
		
		if (event->is<sf::Event::Closed>())
		{
			m_running = false;
		}
		
		auto& playerInput = player()->get<CInput>();
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case sf::Keyboard::Scancode::Escape:
				setPaused(!m_paused);
				break;
			case sf::Keyboard::Scancode::W:
				playerInput.up = true;
				break;
			case sf::Keyboard::Scancode::A:
				playerInput.left = true;
				break;
			case sf::Keyboard::Scancode::S:
				playerInput.down = true;
				break;
			case sf::Keyboard::Scancode::D:
				playerInput.right = true;
				break;
			default: break;
			}
		}

		if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			switch (keyReleased->scancode)
			{
			case sf::Keyboard::Scancode::Escape:
				break;
			case sf::Keyboard::Scancode::W:
				playerInput.up = false;
				break;
			case sf::Keyboard::Scancode::A:
				playerInput.left = false;
				break;
			case sf::Keyboard::Scancode::S:
				playerInput.down = false;
				break;
			case sf::Keyboard::Scancode::D:
				playerInput.right = false;
				break;
			default: break;
			}
		}
	}
}

void Game::setPaused(bool paused)
{
	m_paused = paused;
}