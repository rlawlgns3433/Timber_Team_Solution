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
	Sides originalDirection = Sides::RIGHT;		 // �⺻���� �̹����� �ٶ󺸰� �ִ� ����


public:
	BranchGo(const std::string& name = "");
	virtual ~BranchGo() = default;

	void Reset()							   override;

	void SetSide(Sides side);										 // ���¿� ���� ���� ����
	Sides GetSide() const { return this->side; }
};