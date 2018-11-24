#include "SoundWave.h"

SoundWave::SoundWave()
{
	wave_.setFillColor({ 0, 0, 0, 0 });
	wave_.setPointCount(1000);
	wave_.setOutlineThickness(5);

	radius_ = 0;
	alpha_ = 255;

	dead_ = false;
	timer_ = sf::Time::Zero;
}

SoundWave::SoundWave(float x, float y)
{
	center_.x = x;
	center_.y = y;


	wave_.setFillColor({ 0, 0, 0, 0 });
	wave_.setPointCount(1000);
	wave_.setOutlineThickness(5);

	radius_ = 0;
	alpha_ = 255;

	dead_ = false;
	timer_ = sf::Time::Zero;
}

void SoundWave::setCenter(float x, float y)
{
	center_.x = x;
	center_.y = y;

	radius_ = 0;
	alpha_ = 255;

	dead_ = false;
	timer_ = sf::Time::Zero;
}

void SoundWave::update(sf::Time elapsedTime)
{
	timer_ += elapsedTime;
	
	if (!dead_)
	{
		radius_ += 500 * elapsedTime.asSeconds();
		alpha_ -= 300 * elapsedTime.asSeconds();

		if (alpha_ < 0) {
			alpha_ = 0;
			dead_ = true;
		}

		wave_.setRadius(radius_);
		wave_.setPosition(center_.x - radius_, center_.y - radius_);
		wave_.setOutlineColor({ 255, 255, 255, (sf::Uint8) alpha_ });

		echo_.detect(center_, radius_);
	}
	echo_.update(elapsedTime);
}

void SoundWave::draw(sf::RenderWindow & window)
{
	//echo_.drawObstacle(window);
	echo_.drawLayout(window);
	window.draw(wave_);
}

bool SoundWave::isDead()
{
	return dead_;
}
