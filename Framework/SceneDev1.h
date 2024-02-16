#pragma once
class SceneDev1 : public Scene
{
protected :

public :
	SceneDev1(SceneIDs id);
	virtual ~SceneDev1();

	SceneDev1(const SceneDev1&)				= delete;
	SceneDev1(SceneDev1&&)					= delete;
	SceneDev1& operator=(const SceneDev1&)	= delete;
	SceneDev1& operator=(SceneDev1&&)		= delete;

	// SceneDev1을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};