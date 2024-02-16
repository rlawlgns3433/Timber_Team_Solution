#include "pch.h"
#include "BranchGo.h"

BranchGo::BranchGo(const std::string& name)
	: SpriteGo(name)
{
}

void BranchGo::Reset()
{
	SetSide(Sides::NONE);
}

void BranchGo::SetSide(Sides side)
{
	this->side = side;
	switch (this->side)
	{
	case Sides::LEFT:
	case Sides::RIGHT:
		SetActive(true);
		SetFlipX(this->originalDirection != side);
		break;
	default:
		SetActive(false);
		break;
	}


}
