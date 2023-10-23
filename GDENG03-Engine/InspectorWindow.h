#pragma once
#include "UINames.h"

class InspectorWindow: public AUIScreen
{
public:
	InspectorWindow(const String name);
	~InspectorWindow();

	void drawUI() override;
};

