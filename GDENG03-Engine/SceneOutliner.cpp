#include "SceneOutliner.h"

#include "UIManager.h"

SceneOutliner::SceneOutliner(const String name) : AUIScreen(name)
{
}

SceneOutliner::~SceneOutliner()
{
}

void SceneOutliner::drawUI()
{
	float xLength = UIManager::WINDOW_WIDTH * 0.2f;
	float yLength = UIManager::WINDOW_HEIGHT * (1.0f - 0.025f);

	float xPos = UIManager::WINDOW_WIDTH - ((UIManager::WINDOW_WIDTH * 0.21f * 2.0f));
	float yPos = UIManager::WINDOW_HEIGHT * 0.025f;

	float xButtonSize = UIManager::WINDOW_WIDTH * 0.19f;
	float yButtonSize = UIManager::WINDOW_HEIGHT * 0.025f;

	ImGui::Begin("SceneOutliner", NULL, ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoMove );
	//Window Specificatioon
	ImGui::SetWindowSize( ImVec2(xLength, yLength));
	ImGui::SetWindowPos(ImVec2(xPos, yPos));

	//GameObject Spawning
	ImGui::Button("Sample", ImVec2(xButtonSize, yButtonSize));
	
	ImGui::End();
}
