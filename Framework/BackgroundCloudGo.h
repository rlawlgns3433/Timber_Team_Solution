#pragma once
#include "BackgroundMovingGo.h"
class BackgroundCloudGo : public BackgroundMovingGo
{
protected :
	BackgroundCloudGo(const BackgroundCloudGo&)				= delete;
	BackgroundCloudGo(BackgroundCloudGo&&)					= delete;
	BackgroundCloudGo& operator=(const BackgroundCloudGo&)	= delete;
	BackgroundCloudGo& operator=(BackgroundCloudGo&&)		= delete;

public :
	BackgroundCloudGo(const std::string& name = "");

	void Update(float dt) override;
	void Reset()		  override;
	void RePosition()	  override;
	void ReScale()		  override;
};