#pragma once
class EngineBackend
{
public:
	static EngineBackend* getInstance();
	static void initialize();
	static void destroy();

	enum EditorMode {
		EDITOR = 0,
		PLAY = 1,
		PAUSED = 2
	};

	void setMode(EditorMode mode);
	bool insideFrameStep();
	void startFrameStep();
	void endFrameStep();
	EditorMode getMode();

private:
	EngineBackend();
	~EngineBackend();

	EngineBackend(EngineBackend const&) {};
	EngineBackend& operator=(EngineBackend const&) {};

	static EngineBackend* sharedInstance;

	EditorMode editorMode = EditorMode::EDITOR;

	bool frameStepping = false;

};

