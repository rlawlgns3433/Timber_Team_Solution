#include "pch.h"
#include "BackgroundMovingGo.h"

BackgroundMovingGo::BackgroundMovingGo(const std::string& name)
	: SpriteGo(name)
{
}

float BackgroundMovingGo::GetSpeed() const
{
	return this->speed;
}

float BackgroundMovingGo::GetSpeedMin() const
{
	return this->speedMin;
}

float BackgroundMovingGo::GetSpeedMax() const
{
	return this->speedMax;
}

sf::FloatRect BackgroundMovingGo::GetBounds() const
{
	return this->bounds;
}

void BackgroundMovingGo::RePosition()
{
}

void BackgroundMovingGo::ReRotation()
{
}

void BackgroundMovingGo::ReScale()
{
}

void BackgroundMovingGo::ReDirection()
{
}
