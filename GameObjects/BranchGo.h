#pragma once
#include "SpriteGo.h"
class BranchGo : public SpriteGo
{
protected:
	BranchGo(const BranchGo&) = delete;
	BranchGo(BranchGo&&) = delete;
	BranchGo& operator=(const BranchGo&) = delete;
	BranchGo& operator=(BranchGo&&) = delete;

	Sides side = Sides::NONE;
	Sides originalDirection = Sides::RIGHT;		 // 기본으로 이미지가 바라보고 있는 방향


public:
	BranchGo(const std::string& name = "");
	virtual ~BranchGo() = default;

	void Reset()							   override;

	void SetSide(Sides side);										 // 상태에 따라 방향 설정
	Sides GetSide() const { return this->side; }
};