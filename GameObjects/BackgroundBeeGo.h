#pragma once
#include "BackgroundMovingGo.h"
class BackgroundBeeGo : public BackgroundMovingGo
{
protected:
	BackgroundBeeGo(const BackgroundBeeGo&)				= delete;
	BackgroundBeeGo(BackgroundBeeGo&&)					= delete;
	BackgroundBeeGo& operator=(const BackgroundBeeGo&)	= delete;
	BackgroundBeeGo& operator=(BackgroundBeeGo&&)		= delete;

	sf::FloatRect bounds = { { 0.f, 540.f }, { 1920.f, 540.f } };
	float time = 0.f;
	float beeChangeDuration = 1.f;
	float beeChangeTime = beeChangeDuration;

public:
	BackgroundBeeGo(const std::string& name);

	void Update(float dt) override;
	void Reset()		  override;
	void ReDirection()	  override;
};