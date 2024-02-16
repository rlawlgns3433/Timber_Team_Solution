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
	COUNT, // SceneÀÇ °³¼ö
};