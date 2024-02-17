#pragma once

class SpriteGo;
class TextGo;

class SceneSelectMode : public Scene
{
protected:
	SpriteGo* background;
	TextGo* pressNumber;
	TextGo* num1ForSinglePlay;
	TextGo* num2ForDuoPlay;


public:
	SceneSelectMode(SceneIDs id);
	virtual ~SceneSelectMode();

	SceneSelectMode(const SceneSelectMode&) = delete;
	SceneSelectMode(SceneSelectMode&&) = delete;
	SceneSelectMode& operator=(const SceneSelectMode&) = delete;
	SceneSelectMode& operator=(SceneSelectMode&&) = delete;

	void selectModeCheckTime();

	// SceneSelectMode을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};

