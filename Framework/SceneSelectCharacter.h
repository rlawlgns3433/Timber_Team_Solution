#pragma once
class SceneSelectCharacter : public Scene
{
protected :

public :
	SceneSelectCharacter(SceneIDs id);
	virtual ~SceneSelectCharacter();

	SceneSelectCharacter(const SceneSelectCharacter&)				= delete;
	SceneSelectCharacter(SceneSelectCharacter&&)					= delete;
	SceneSelectCharacter& operator=(const SceneSelectCharacter&)	= delete;
	SceneSelectCharacter& operator=(SceneSelectCharacter&&)		= delete;

	// SceneSelectCharacter��(��) ���� ��ӵ�
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
};