#include "UIManager.h"

#include "EngineProfiler.h"
#include "InspectorWindow.h"
#include "SceneOutliner.h"
#include "ScenePlaySettings.h"

UIManager* UIManager::sharedInstance = nullptr;


UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{

	sharedInstance = new UIManager(windowHandle);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirectD3D11Device(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

	sharedInstance->OnCreateInterface();
}

void UIManager::destroy()
{
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for(int i = 0; i < this->uiList.size(); i++)
	{
		this->uiList[i]->drawUI();
	}



	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

UIManager::UIManager(HWND windowHandle)
{
}

UIManager::~UIManager()
{

}

void UIManager::OnCreateInterface()
{
	Toolbar* toolbar = new Toolbar("New");
	uiList.push_back(toolbar);

	SceneOutliner* sceneOutliner = new SceneOutliner("New");
	uiList.push_back(sceneOutliner);

	InspectorWindow* inspectorWindow = new InspectorWindow("New");
	uiList.push_back(inspectorWindow);

	EngineProfiler* engineProfiler = new EngineProfiler("New");
	uiList.push_back(engineProfiler);

	ScenePlaySettings* scenePlaySettings = new ScenePlaySettings("New");
	uiList.push_back(scenePlaySettings);
}