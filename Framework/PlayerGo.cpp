#include "pch.h"
#include "PlayerGo.h"


PlayerGo::PlayerGo(const std::string& name)
	: SpriteGo(name)
{
}

void PlayerGo::Init()
{
	if (SCENEMANAGER.GetMode() == SceneManager::Mod::SINGLE)
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

	if (SCENEMANAGER.GetMode() == SceneManager::Mod::DUO)
	{
		SetOrigin(Origins::BC);
		SetTexture(*TEXTURE_MANAGER.GetResource(playerId));
		axe.SetActive(true);
		axe.SetFlipX(true);
		axe.SetTexture(*TEXTURE_MANAGER.GetResource(axeId));
		//position을 sceneDuo에서 잡아주기
	}
}

void PlayerGo::Release()
{
}

void PlayerGo::Reset()
{
	if (SCENEMANAGER.GetMode() == SceneManager::Mod::SINGLE)
	{
		isDead = false;
		SetTexture(*TEXTURE_MANAGER.GetResource(playerId));
		SetPosition({ CenterX + playerOffsetX, 580 });
		SetFlipX(false);

		axe.SetPosition({ CenterX + playerOffsetX + 20, 720 });
		axe.SetFlipX(true);
		state = PlayerState::ALIVE;
	}

	if (SCENEMANAGER.GetMode() == SceneManager::Mod::DUO)
	{
		isDead = false;
		SetTexture(*TEXTURE_MANAGER.GetResource(playerId));
		SetFlipX(false);

		axe.SetFlipX(true);
		state = PlayerState::ALIVE;
	}
}

void PlayerGo::Update(float dt)
{
	//Single Mode
	if (SCENEMANAGER.GetMode() == SceneManager::Mod::SINGLE)
	{
		if (playerSide == Sides::LEFT)
		{
			SetPosition({ CenterX - playerOffsetX, 580 });
			axe.SetPosition({ CenterX - playerOffsetX - 20, 720 });
			axe.SetFlipX(false);
			axe.SetSide(Sides::LEFT);
			SetFlipX(true);
		}
		else if (playerSide == Sides::RIGHT)
		{
			SetPosition({ CenterX + playerOffsetX, 580 });
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

	//Duo Mode
	if (SCENEMANAGER.GetMode() == SceneManager::Mod::DUO)
	{
		if (playerSide == Sides::LEFT)
		{
			axe.SetPosition({ GetPosition().x - 100.f, 770.f});
			axe.SetFlipX(false);
			axe.SetSide(Sides::LEFT);
			SetFlipX(true);
		}
		else if (playerSide == Sides::RIGHT)
		{
			axe.SetPosition({ GetPosition().x + 100.f, 770.f});
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
