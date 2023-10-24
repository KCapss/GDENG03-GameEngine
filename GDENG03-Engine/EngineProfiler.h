#pragma once
#include "UINames.h"
#include <iomanip>

class EngineProfiler: public AUIScreen
{
public:
	EngineProfiler(const String name);
	~EngineProfiler();

	void drawUI() override;
};

