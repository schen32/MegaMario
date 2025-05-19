#include "GameEngine.h"
#include "Assets.hpp"
#include "Scene_Menu.h"
#include "Scene_Play.h"

#include <fstream>
#include <iostream>

GameEngine::GameEngine(const std::string& path)
{
	init(path);
}

void GameEngine::init(const std::string& path)
{
	m_assets.loadFromFile(path);

	unsigned int wWidth = 0, wHeight = 0;
	m_window.create(sf::VideoMode({ wWidth, wHeight }), "MegaMario",
		sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);

	ImGui::SFML::Init(m_window);

	changeScene("MENU", std::make_shared<Scene_Menu>(this));
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning()
{
	return m_running && m_window.isOpen();
}

sf::RenderWindow& GameEngine::window()
{
	return m_window;
}

void GameEngine::run()
{
	while (isRunning())
	{
		update();
		ImGui::SFML::Update(m_window, m_deltaClock.restart());
	}
}

void GameEngine::sUserInput()
{
	while (const std::optional event = m_window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(m_window, *event);

		if (event->is<sf::Event::Closed>())
		{
			quit();
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::X)
			{
				auto texture = sf::Texture(m_window.getSize());
				texture.update(m_window);
				if (texture.copyToImage().saveToFile("test.png"))
				{
					std::cout << "Screenshot Saved: " << "test.png" << std::endl;
				}
			}
		}
		
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (currentScene()->getActionMap().find(static_cast<int>(keyPressed->scancode)) ==
				currentScene()->getActionMap().end())
			{
				continue;
			}
			currentScene()->doAction
			(
				Action
				(
				currentScene()->getActionMap().at(static_cast<int>(keyPressed->scancode)),
				"START"
				)
			);
		}

		if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			if (currentScene()->getActionMap().find(static_cast<int>(keyReleased->scancode)) ==
				currentScene()->getActionMap().end())
			{
				continue;
			}
			currentScene()->doAction
			(
				Action
				(
					currentScene()->getActionMap().at(static_cast<int>(keyReleased->scancode)),
					"END"
				)
			);
		}
	}
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene,
	bool endCurrentScene)
{
	if (scene)
	{
		m_sceneMap[sceneName] = scene;
	}
	else if (m_sceneMap.find(sceneName) == m_sceneMap.end())
	{
		std::cerr << "Warning: Scene does not exist: " << sceneName << std::endl;
		return;
	}

	if (endCurrentScene)
	{
		m_sceneMap.erase(m_sceneMap.find(m_currentScene));
	}
	m_currentScene = sceneName;
}

void GameEngine::quit()
{
	m_running = false;
}

const Assets& GameEngine::assets() const
{
	return m_assets;
}

void GameEngine::update()
{
	if (!isRunning()) return;
	if (m_sceneMap.empty()) return;

	sUserInput();
	currentScene()->simulate(m_simulationSpeed);
	currentScene()->sRender();

	m_window.display();
}