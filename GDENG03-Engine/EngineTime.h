#pragma once
//Class storing of frame ticks

#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&); // copy  constructor
	EngineTime& operator=(EngineTime const&){} // assignment operator

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;
};

