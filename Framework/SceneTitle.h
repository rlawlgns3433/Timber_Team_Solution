#pragma once
class SceneTitle : public Scene
{
protected:

public:
	SceneTitle(SceneIDs id);
	virtual ~SceneTitle();

	SceneTitle(const SceneTitle&) = delete;
	SceneTitle(SceneTitle&&) = delete;
	SceneTitle& operator=(const SceneTitle&) = delete;
	SceneTitle& operator=(SceneTitle&&) = delete;

	// SceneTitle��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};