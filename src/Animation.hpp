#pragma once

#include "Vec2.hpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>

class Animation
{
public:
	sf::Texture m_texture;
	sf::Sprite m_sprite = sf::Sprite(m_texture);
	size_t m_frameCount = 1; // total number of frames of animation
	size_t m_currentFrame = 0; // the current frame of animation being played
	size_t m_speed = 0; // the speed or duration to play this animation
	Vec2<size_t> m_size = { 1, 1 }; // size of the animation frame
	std::string m_name = "none";

	Animation() = default;
	Animation(const std::string& name, const sf::Texture& t)
		: Animation(name, t, 1, 0) { }
	Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed)
		: m_name(name), m_sprite(t)
		, m_frameCount(frameCount), m_currentFrame(0), m_speed(speed)
	{ }

	void update()
	{
		
	}

	bool hasEnded() const
	{
		
	}
};