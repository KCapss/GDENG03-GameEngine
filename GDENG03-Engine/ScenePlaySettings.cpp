#include "ScenePlaySettings.h"
#include "GameObjectManager.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "EngineBackend.h"
#include "AGameObject.h"
#include "imgui.h"


ScenePlaySettings::ScenePlaySettings(std::string name) : AUIScreen(name)
{
}

ScenePlaySettings::~ScenePlaySettings()
{
}

void ScenePlaySettings::drawUI()
{
	EngineBackend* backend = EngineBackend::getInstance();

	ImGui::Begin("Scene Play Options", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 75));
	ImGui::SameLine();

	//TODO: Use memento pattern for saving state of objects
	if (backend->getMode() == EngineBackend::EDITOR) {
		if (ImGui::Button("Play"))
		{
			EngineBackend::getInstance()->setMode(EngineBackend::PLAY);

			PhysicsSystem::ComponentList components = BaseComponentSystem::getInstance()->getPhysicsSystem()->getAllComponents();
			for (int i = 0; i < components.size(); i++) {
				if (components[i]->getRigidBody()->getType() == BodyType::DYNAMIC)
				{
					AGameObject* aObject = components[i]->getOwner();

					aObject->detachComponent(components[i]);
					BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(components[i]);

					//copy Component Properties:

					string componentName = "Physics_Component ";
					aObject->attachComponent(new PhysicsComponent(componentName.append(aObject->RetrieveName()), aObject, BodyType::DYNAMIC));

					AGameObject::ComponentList list = aObject->getComponentsOfType(AComponent::ComponentType::Physics);
					PhysicsComponent* pObject = (PhysicsComponent*)list[0];

					pObject->getRigidBody()->setMass((components[i]->getRigidBody()->getMass()));
					pObject->getRigidBody()->enableGravity((components[i]->getRigidBody()->isGravityEnabled()));

					delete components[i];
				}

			}
		}
	}

	else if (backend->getMode() != EngineBackend::EDITOR) {
		if (ImGui::Button("Stop")) 
			EngineBackend::getInstance()->setMode(EngineBackend::EDITOR); 
	}

	ImGui::SameLine();

	if (backend->getMode() == EngineBackend::PLAY) {
		if (ImGui::Button("Pause"))
			EngineBackend::getInstance()->setMode(EngineBackend::PAUSED);
		
	}
	else if (backend->getMode() == EngineBackend::PAUSED) {
		if (ImGui::Button("Resume"))
			EngineBackend::getInstance()->setMode(EngineBackend::PLAY);
	}

	ImGui::SameLine();
	if (backend->getMode() == EngineBackend::PAUSED && ImGui::Button("Frame Step"))
		EngineBackend::getInstance()->startFrameStep();
	
	ImGui::End();
}
