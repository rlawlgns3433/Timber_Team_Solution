#pragma once
class SceneDev2 : public Scene
{
protected:

public:
	SceneDev2(SceneIDs id);
	virtual ~SceneDev2();

	SceneDev2(const SceneDev2&)				= delete;
	SceneDev2(SceneDev2&&)					= delete;
	SceneDev2& operator=(const SceneDev2&)	= delete;
	SceneDev2& operator=(SceneDev2&&)		= delete;

	// SceneDev2을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};

