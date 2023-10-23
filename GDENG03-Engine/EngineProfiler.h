#pragma once
#include "UINames.h"

class EngineProfiler: public AUIScreen
{
public:
	EngineProfiler(const String name);
	~EngineProfiler();

	void drawUI() override;
};

