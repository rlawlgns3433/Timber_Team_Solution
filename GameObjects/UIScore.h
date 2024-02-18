#pragma once
#include "TextGo.h"

class UIScore : public TextGo
{
protected:
	UIScore(const UIScore&)				 = delete;
	UIScore(UIScore&&)					 = delete;
	UIScore& operator=(const UIScore&)	 = delete;
	UIScore& operator=(UIScore&&)		 = delete;

	std::string scoreFormat = "Score : ";
	unsigned score; // �ٸ� Ŭ������ ����


public:
	UIScore(const std::string& name = "");

	std::string GetScore() { return this->scoreFormat.append(std::to_string(score)); }
	unsigned GetUnsignedScore() const { return score; }
	void SetScore(size_t score);
	void AddScore(size_t score);

	void Reset() override;

};