#include "InspectorWindow.h"
#include "UIManager.h"

InspectorWindow::InspectorWindow(const String name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
	bool dare = false;
	float copy[3] = { 0,0,0 };

	float xLength = UIManager::WINDOW_WIDTH * 0.2f;
	float yLength = UIManager::WINDOW_HEIGHT * (1.0f - 0.025f);

	float xPos = UIManager::WINDOW_WIDTH - ((UIManager::WINDOW_WIDTH * 0.22f));
	float yPos = UIManager::WINDOW_HEIGHT * 0.025f;

	float xButtonSize = UIManager::WINDOW_WIDTH * 0.19f;
	float yButtonSize = UIManager::WINDOW_HEIGHT * 0.025f;

	ImGui::Begin("Inspector Window", NULL, ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove);
	//Window Specificatioon
	ImGui::SetWindowSize(ImVec2(xLength, yLength));
	ImGui::SetWindowPos(ImVec2(xPos, yPos));

	//TODO: CREATE THE FF
	// 1) Text = Selected Object: (Primitive Type)
	// 2) Checkbox default
	// 3) Transform (3 Inputs) per type (Transform, Rotate-Euler, Scale -> Same Line (Transform Type)
	//
	//

	ImGui::TextWrapped("No Object Selected, Select an object");

	ImGui::Checkbox("Enabled", &dare);
	ImGui::InputFloat3("Position", copy);
	
	ImGui::End();
}
