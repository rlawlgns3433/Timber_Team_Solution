#pragma once
class SceneTitle : public Scene
{
protected:
	std::string backgroundId = "graphics/background.png";
	std::string cloudId = "graphics/cloud.png";
	std::string beeId = "graphics/bee.png";
	std::string treeId = "graphics/tree.png";
	std::string branchId = "graphics/branch.png";
	std::string logId = "graphics/log.png";
	std::string fontId = "fonts/KOMIKAP_.ttf";
	std::string playerId = "graphics/player.png";
	std::string ripId = "graphics/rip.png";
	std::string axeId = "graphics/axe.png";
	std::string chopId = "sound/chop.wav";
	std::string deathId = "sound/death.wav";
	std::string outOfTimeId = "sound/out_of_time.wav";
	std::string bgmId = "sound/kerning.mp3";


public:
	SceneTitle(SceneIDs id);
	virtual ~SceneTitle();

	SceneTitle(const SceneTitle&) = delete;
	SceneTitle(SceneTitle&&) = delete;
	SceneTitle& operator=(const SceneTitle&) = delete;
	SceneTitle& operator=(SceneTitle&&) = delete;

	// SceneTitle을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;

	void LoadAllResources();
};