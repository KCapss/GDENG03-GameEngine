#include "Toolbar.h"

#include "Cube.h"
#include "GameObjectManager.h"
#include "SceneReader.h"
#include "SceneWriter.h"
#include "UIManager.h"

Toolbar::Toolbar(const string name) : AUIScreen(name)
{
	saveFileDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	saveFileDialog->SetTitle("Save Scene");
	saveFileDialog->SetTypeFilters({ ".level" });

	openFileDialog = new ImGui::FileBrowser();
	openFileDialog->SetTitle("Open Scene");
	openFileDialog->SetTypeFilters({ ".level", ".unity" });
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
			if (ImGui::MenuItem("New")) {
				saveFileDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+s")) {
				saveFileDialog->Open();
			}
			if (ImGui::MenuItem("Open", "Ctrl+o")) {
				openFileDialog->Open();
			}
			if (ImGui::MenuItem("Exit")) {
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::MenuItem("Create Sphere"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE, shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();
			}

			if (ImGui::MenuItem("Create Cube"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();
			}

			if (ImGui::MenuItem("Create Textured Cube"))
			{
			}

			if (ImGui::MenuItem("Create Placeholder Physics Cube"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE, shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();
			}
			
			if (ImGui::MenuItem("Create Plane"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();
			}

			if (ImGui::MenuItem("Create Placeholder Physics Plane"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_PLANE, shader_byte_code, size_shader);
				
			}
			if (ImGui::BeginMenu("Create Light"))
			{
				if (ImGui::MenuItem("Point Light")) {}
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Batch P6 Cube"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->batchInstantiate(shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();
			}
			
			ImGui::EndMenu();

		}

		ImGui::EndMainMenuBar();

		openFileDialog->Display();
		saveFileDialog->Display();
		if (openFileDialog->HasSelected())
		{
			// Full File Path fileDialog.GetSelected().string()
			//std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;

			SceneReader* reader = new SceneReader(openFileDialog->GetSelected().string());
			reader->readFromFile();
			openFileDialog->ClearSelected();
			openFileDialog->Close();
		}

		if (saveFileDialog->HasSelected())
		{
			// Full File Path fileDialog.GetSelected().string()
			//std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
			SceneWriter* file = new SceneWriter();
			file->setDirectory(saveFileDialog->GetSelected().string());
			file->writeToFile();
			saveFileDialog->ClearSelected();
			saveFileDialog->Close();
		}
	}
		
	
}
