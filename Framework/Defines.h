#pragma once

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class Sides
{
	NONE = -1,
	LEFT,
	RIGHT,
	COUNT
};

enum class SceneIDs
{
	None = -1,
	SceneTitle,
	SceneSelectMode,
	SceneSelectCharacter,
	SceneGameSingle,
	SceneGameDuo,
	COUNT, // SceneÀÇ °³¼ö
};

enum class PlayerSelectCharacter
{
	None = -1,
	WoodCutter,
	YoungWoodCutter,
	COUNT,
};

enum class PlayerState
{
	NOTSET = -1,
	ALIVE,
	DEAD
};