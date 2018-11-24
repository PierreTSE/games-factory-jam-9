#include "SoundWave.h"

SoundWave::SoundWave()
{
	wave_.setFillColor({ 0, 0, 0, 0 });
	wave_.setPointCount(1000);
	wave_.setOutlineThickness(5);

	radius_ = 0;
	alpha_ = 255;

	radiusSpeed_ = 600;
	alphaSpeed_ = 600;

	timer_ = sf::Time::Zero;
}

SoundWave::SoundWave(float x, float y)
{
	center_.x = x;
	center_.y = y;

	radiusSpeed_ = 600;
	alphaSpeed_ = 600;

	wave_.setFillColor({ 0, 0, 0, 0 });
	wave_.setPointCount(1000);
	wave_.setOutlineThickness(5);

	radius_ = 0;
	alpha_ = 255;

	timer_ = sf::Time::Zero;
}

void SoundWave::setCenter(float x, float y)
{
	center_.x = x;
	center_.y = y;
}

void SoundWave::update()
{
	auto elapsedTime = globalClock::getClock().frameTime();
	timer_ += elapsedTime;
	
	if (alpha_ != 0)
	{
		radius_ += radiusSpeed_ * elapsedTime.asSeconds();
		alpha_ -= alphaSpeed_ * elapsedTime.asSeconds();

		if (alpha_ < 0) {
			alpha_ = 0;
		}

		wave_.setRadius(radius_);
		wave_.setPosition(center_.x - radius_, center_.y - radius_);
		wave_.setOutlineColor({ 255, 255, 255, (sf::Uint8) alpha_ });
		echo_.detect(center_, radius_);
	}
	echo_.update(elapsedTime);
}

void SoundWave::setRadiusSpeed(float sp)
{
	radiusSpeed_ = sp;
}

void SoundWave::setAlphaSpeed(float sp)
{
	alphaSpeed_ = sp;
}

void SoundWave::setRadius(float r)
{
	radius_ = r;
}

void SoundWave::setAlpha(float a)
{
	alpha_ = a;
}

void SoundWave::draw(sf::RenderWindow & window)
{
	//echo_.drawObstacle(window);
	echo_.drawLayout(window);

	if(drawCircle)
		window.draw(wave_);
}

bool SoundWave::isDead()
{
	return echo_.isDead();
}

void SoundWave::setDrawCircle(bool b)
{
	drawCircle = b;
}

sf::Time SoundWave::getTime()
{
	return timer_;
}
