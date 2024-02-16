#pragma once
#include "SpriteGo.h"
#include "AxeGo.h"

class PlayerGo : public SpriteGo
{
public :
	enum class PlayerState
	{
		NOTSET,
		ALIVE,
		DEAD
	};

protected:
	PlayerGo(const PlayerGo&)		 	 = delete;
	PlayerGo(PlayerGo&&)				 = delete;
	PlayerGo& operator=(const PlayerGo&) = delete;
	PlayerGo& operator=(PlayerGo&&)		 = delete;


	PlayerState state = PlayerState::NOTSET;
	Sides playerSide;
	AxeGo axe;

	bool isDead = false;
	bool isAxeActive = false;

	float CenterX;
	float playerOffsetX = 200.f;

	std::string playerId = "graphics/player.png";
	std::string ripId = "graphics/rip.png";
	std::string axeId = "graphics/axe.png";

public:
	PlayerGo(const std::string& name = "");
	virtual ~PlayerGo() = default;

	void Init()							override;
	void Release()						override;
	void Reset()						override;
	void Update(float dt)				override;
	void Draw(sf::RenderWindow& window) override;

	Sides GetPlayerSide() const { return this->playerSide; }
	void UpdatePlayerSide(Sides Sides);
	void SetDead();
	PlayerState IsDead() const { return this->state; }
	void SetAxeActive(bool active) { this->isAxeActive = active; }
	bool IsAxeActive() { return this->isAxeActive; }
};