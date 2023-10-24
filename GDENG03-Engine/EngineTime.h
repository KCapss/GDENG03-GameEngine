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
	static double GetFPS();
	static double GetmsPerFrame();


private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&); // copy  constructor
	EngineTime& operator=(EngineTime const&){} // assignment operator
	

	
	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	double deltaTime = 0;
	double msPerFrame = 0;
	int frames = 0;
	int fps = 0;

	void UpdateFrames();
	
	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;
};

