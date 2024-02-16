#pragma once
#include "SpriteGo.h"
class BackgroundMovingGo : public SpriteGo
{
protected :
	BackgroundMovingGo(const BackgroundMovingGo&)				= delete;
	BackgroundMovingGo(BackgroundMovingGo&&)					= delete;
	BackgroundMovingGo& operator=(const BackgroundMovingGo&)	= delete;
	BackgroundMovingGo& operator=(BackgroundMovingGo&&)			= delete;

	sf::FloatRect bounds = { 0.f, 0.f, 1920.f, 1080.f };

	float speed = 100.f;
	float speedMin = 100.f;
	float speedMax = 200.f;

	sf::Vector2f direction = { 1.f, 0.f };

public :
	BackgroundMovingGo(const std::string& name = "");

	sf::FloatRect GetBounds() const;
	void SetBounds(const sf::FloatRect& bounds) { this->bounds = bounds; }
	float GetSpeed() const;
	void SetSpeed(const float& speed) { this->speed = speed; }
	float GetSpeedMin() const;
	void SetMinSpeed(const float& minSpeed) { this->speedMin = minSpeed; }
	float GetSpeedMax() const;
	void SetMaxSpeed(const float& maxSpeed) { this->speedMax = maxSpeed; }

	virtual void RePosition();
	virtual void ReRotation();
	virtual void ReScale();

	virtual void ReDirection();
};