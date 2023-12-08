#pragma once
#include "AUIScreen.h"
class ScenePlaySettings: public AUIScreen
{
	ScenePlaySettings(std::string name);
	~ScenePlaySettings();

	virtual void drawUI() override;

	friend class UIManager;


	bool isPlay = false;
	bool isPaused = false;
};

