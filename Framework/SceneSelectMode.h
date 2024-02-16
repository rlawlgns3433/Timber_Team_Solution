#pragma once
class SceneSelectMode : public Scene
{
protected:

public:
	SceneSelectMode(SceneIDs id);
	virtual ~SceneSelectMode();

	SceneSelectMode(const SceneSelectMode&)				= delete;
	SceneSelectMode(SceneSelectMode&&)					= delete;
	SceneSelectMode& operator=(const SceneSelectMode&)	= delete;
	SceneSelectMode& operator=(SceneSelectMode&&)		= delete;

	// SceneSelectMode��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};

