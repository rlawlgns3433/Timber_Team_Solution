#include "pch.h"
#include "TreeGo.h"
#include "BranchGo.h"

TreeGo::TreeGo(const std::string& name)
	: GameObject(name)
{
}


void TreeGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	tree.setPosition(pos);
	UpdateBranchPosition();
}

void TreeGo::SetOrigin(Origins preset)
{
	if (preset == Origins::CUSTOM)
	{
		preset == Origins::TL;
	}

	originPreset = preset;
	Utils::SetOrigin(tree, originPreset);
}

void TreeGo::SetOrigin(const sf::Vector2f& origin)
{
	originPreset = Origins::CUSTOM;
	this->origin = origin;
}

void TreeGo::Init()
{
	Release();

	tree.setTexture(*TEXTURE_MANAGER.GetResource(treeTextureId));
	Utils::SetOrigin(tree, Origins::BC);

	sf::Texture& branchTexture = *TEXTURE_MANAGER.GetResource(branchTextureId);

	float originBranchX = tree.getLocalBounds().width * -0.5f;
	float originBranchY = branchTexture.getSize().y;

	branchTexture.getSize().y;
	for (size_t i = 0; i < branchCount; ++i)
	{
		BranchGo* branch = new BranchGo;
		branch->SetTexture(*TEXTURE_MANAGER.GetResource(branchTextureId));
		branch->SetOrigin({ originBranchX, originBranchY });
		branches.push_back(branch);
	}
}

void TreeGo::Release()
{
	for (BranchGo* branch : branches)
	{
		delete branch;
	}
	branches.clear();
}

void TreeGo::Reset()
{
	for (BranchGo* branch : branches)
	{
		branch->Reset();
	}

	noneCount = 2;
	int count = 0;

	for (BranchGo* branch : branches)
	{
		if (count < noneCount)
		{
			branch->SetSide(Sides::NONE);
		}
		else
		{
			branch->SetSide(RandomSide());
		}
		++count;
	}
	UpdateBranchPosition();
}

void TreeGo::Update(float dt)
{
	for (BranchGo* branch : branches)
	{
		if (branch->GetActive())
		{
			branch->Update(dt);
		}
	}
}

void TreeGo::Draw(sf::RenderWindow& window)
{
	window.draw(tree);
	for (BranchGo* branch : branches)
	{
		if (branch->GetActive())
		{
			branch->Draw(window);
		}
	}
}

Sides TreeGo::Chop(Sides side)
{
	BranchGo* temp = branches.front();
	branches.pop_front();
	temp->SetSide(RandomSide());
	branches.push_back(temp);

	// TODO : 가지 이동
	UpdateBranchPosition();

	return branches.front()->GetSide();
}

Sides TreeGo::GetFirstBranch() const
{
	return branches.front()->GetSide();
}

void TreeGo::UpdateBranchPosition()
{
	sf::Vector2f branchPos = position;

	for (BranchGo* branch : branches)
	{
		branchPos.y -= branchOffsetY;
		branch->SetPosition(branchPos);
	}
}

Sides TreeGo::RandomSide(int range)
{
	Sides side = Sides::NONE;
	int rand = Utils::RandomRange(0, range);

	if (rand < 2)
	{
		side = (Sides)rand;
	}
	return side;
}