#include "pch.h"
#include "PlayerGo.h"

PlayerGo::PlayerGo(const std::string& name)
	: SpriteGo(name)
{
}

void PlayerGo::Init()
{
	CenterX = FRAMEWORK.GetWindowSize().x / 2;

	SetOrigin(Origins::BC);
	SetPosition({ CenterX + playerOffsetX, 600 });
	SetTexture(*TEXTURE_MANAGER.GetResource(playerId));

	axe.SetActive(true);
	axe.SetPosition({ CenterX + playerOffsetX + 20, 720 });
	axe.SetFlipX(true);
	axe.SetTexture(*TEXTURE_MANAGER.GetResource(axeId));
}

void PlayerGo::Release()
{
}

void PlayerGo::Reset()
{
	isDead = false;
	SetTexture(*TEXTURE_MANAGER.GetResource(playerId));
	SetPosition({ CenterX + playerOffsetX, 600 });
	SetFlipX(false);

	axe.SetActive(true);
	axe.SetPosition({ CenterX + playerOffsetX + 20, 720 });
	axe.SetFlipX(true);
}

void PlayerGo::Update(float dt)
{
	if (playerSide == Sides::LEFT)
	{
		SetPosition({ CenterX - playerOffsetX, 600 });
		axe.SetPosition({ CenterX - playerOffsetX - 20, 720 });
		axe.SetFlipX(false);
		axe.SetSide(Sides::LEFT);
		SetFlipX(true);
	}
	else if (playerSide == Sides::RIGHT)
	{
		SetPosition({ CenterX + playerOffsetX, 600 });
		axe.SetPosition({ CenterX + playerOffsetX + 20, 720 });
		axe.SetFlipX(true);
		axe.SetSide(Sides::RIGHT);
		SetFlipX(false);
	}

	if (isAxeActive) axe.SetActive(true);
	else axe.SetActive(false);

	if (state == PlayerState::DEAD)
	{
		axe.SetActive(false);
	}
}

void PlayerGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (axe.GetActive())
	{
		axe.Draw(window);
	}
}

void PlayerGo::UpdatePlayerSide(Sides side)
{
	playerSide = side;

}

void PlayerGo::SetDead()
{
	this->state = PlayerState::DEAD;
	SetTexture(*TEXTURE_MANAGER.GetResource(ripId));
}
