#pragma once
#include "SpriteGo.h"
class EffectLog : public SpriteGo
{
protected:
	EffectLog(const EffectLog&)			   = delete;
	EffectLog(EffectLog&&)				   = delete;
	EffectLog& operator=(const EffectLog&) = delete;
	EffectLog& operator=(EffectLog&&)	   = delete;

	sf::Vector2f gravity = { 0.f, 500.f };
	sf::Vector2f velocity;


public:
	// protected 멤버로 이동 필요
	float duration = 3.f;
	float timer = 0.f;

	EffectLog(const std::string& name = "");
	virtual ~EffectLog()					= default;

	void Update(float dt) override;

	void Fire(const sf::Vector2f& velocity);
};