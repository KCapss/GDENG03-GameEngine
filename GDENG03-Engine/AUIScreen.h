#pragma once
#include <string>

class  UIManager;

class AUIScreen
{
protected:
	typedef std::string String;

	AUIScreen(String name);
	~AUIScreen();

	String getName();
	virtual void drawUI();

	String name;

	friend class UIManager;
};

