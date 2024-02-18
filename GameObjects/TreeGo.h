#pragma once
#include "GameObject.h"

class BranchGo;

class TreeGo : public GameObject
{
protected:
	TreeGo(const TreeGo&) = delete;
	TreeGo(TreeGo&&) = delete;
	TreeGo& operator=(const TreeGo&) = delete;
	TreeGo& operator=(TreeGo&&) = delete;

	sf::Sprite tree;
	std::list<BranchGo*> branches;
	int noneCount = 0;
	float branchOffsetY = 150.f;

public:
	int	branchCount = 6;
	std::string treeTextureId = "graphics/tree.png";
	std::string branchTextureId = "graphics/branch.png";

	TreeGo(const std::string& name = "");
	virtual ~TreeGo() = default;

	void SetBranchCount(size_t count) { branchCount = count; } // 초기화 용도로 사용

	void SetPosition(const sf::Vector2f& pos)	override;
	void SetOrigin(Origins preset)				override;
	void SetOrigin(const sf::Vector2f& origin) override;

	void Init()							override;
	void Release()						override;
	void Reset()						override;
	void Update(float dt)				override;
	void Draw(sf::RenderWindow& window) override;

	Sides Chop(Sides side);										// 새로 채워진 가지의 위치를 리턴
	Sides GetFirstBranch() const;
	void UpdateBranchPosition();

	static Sides RandomSide(int range = 4);
};

