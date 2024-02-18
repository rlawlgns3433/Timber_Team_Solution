#pragma once
class SpriteGo;
class TextGo;

class SceneSelectCharacter : public Scene
{
protected :
	SpriteGo* spriteGoBackground;
	SpriteGo* spritePlayer1;
	SpriteGo* spritePlayer2;
	TextGo* SelectText;

	PlayerSelectCharacter playerOneSelectCharacter = PlayerSelectCharacter::None;
	PlayerSelectCharacter playerTwoSelectCharacter = PlayerSelectCharacter::None;

public :
	SceneSelectCharacter(SceneIDs id);
	virtual ~SceneSelectCharacter();

	SceneSelectCharacter(const SceneSelectCharacter&)				= delete;
	SceneSelectCharacter(SceneSelectCharacter&&)					= delete;
	SceneSelectCharacter& operator=(const SceneSelectCharacter&)	= delete;
	SceneSelectCharacter& operator=(SceneSelectCharacter&&)		= delete;

	// SceneSelectCharacter을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};