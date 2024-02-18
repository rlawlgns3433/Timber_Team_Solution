#include "pch.h"
#include "EffectLog.h"

EffectLog::EffectLog(const std::string& name)
	: SpriteGo(name)
{
}

void EffectLog::Update(float dt)
{
	timer += dt;

	if (timer > duration)
	{
		SetActive(false);
		return;
	}

	velocity += gravity * dt;

	// 등가속도 운동

	SetPosition(position + velocity * dt); // dx =  vdt
}

void EffectLog::Fire(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
	timer = 0.f;
}
