#include "Toolbar.h"

#include "UIManager.h"

Toolbar::Toolbar(const string name) : AUIScreen(name)
{
	
}

Toolbar::~Toolbar()
{
}

void Toolbar::drawUI()
{
	//ImGui::ShowDemoWindow(); // Show demo window! :)

	
	if (ImGui::BeginMainMenuBar()) {


		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Create")) {
			}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
			}
			if (ImGui::MenuItem("Save as..")) {
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::MenuItem("Create Cube")) {}
			if (ImGui::MenuItem("Create Sphere")) {}
			if (ImGui::MenuItem("Create Plane")) {}
			if (ImGui::BeginMenu("Create Light"))
			{
				if (ImGui::MenuItem("Point Light")) {}
				ImGui::EndMenu();
			}
			
			ImGui::EndMenu();

		}

		ImGui::EndMainMenuBar();
	}
		
	
}
