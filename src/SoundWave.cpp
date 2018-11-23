#include "SoundWave.h"

SoundWave::SoundWave(float x, float y)
{
	center_.x = x;
	center_.y = y;


	wave_.setFillColor({ 0, 0, 0, 0 });
	wave_.setPointCount(1000);
	wave_.setOutlineThickness(5);

	radius_ = 0;
	alpha_ = 255;
}

void SoundWave::update(sf::Time elapsedTime)
{
	radius_ += 400 * elapsedTime.asSeconds();
	alpha_ -= 255 * elapsedTime.asSeconds();

	if (alpha_ < 0)
		alpha_ = 0;

	wave_.setRadius(radius_);
	wave_.setPosition(center_.x - radius_, center_.y - radius_);
	wave_.setOutlineColor({ 255, 255, 255, (sf::Uint8) alpha_ });
}

void SoundWave::draw(sf::RenderWindow & window)
{
	window.draw(wave_);
}
