#include "InputSystem.h"

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	delete sharedInstance;
}

InputSystem::InputSystem()
{
	this->oldMousePos = Point(0, 0);
}

InputSystem::~InputSystem()
{
	this->inputListenerList.clear();
}


void InputSystem::addListener(InputListener* listener)
{
	this->inputListenerList.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	//find object in used
	int index = -1;
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		if (this->inputListenerList[i] == listener) {
			index = i;
			break;
		}
	}
	if (index > -1) {
		this->inputListenerList.erase(this->inputListenerList.begin() + index);
	}
}

void InputSystem::update()
{
	POINT currentPt = {};
	GetCursorPos(&currentPt);

	if (firstTimeCall) {
		firstTimeCall = false;
		this->oldMousePos = Point(currentPt.x, currentPt.y);
	}

	// if mouse position changed
	if (oldMousePos.getX() != currentPt.x || oldMousePos.getY() != currentPt.y)
	{
		Point deltaPt = Point(currentPt.x - oldMousePos.getX(), currentPt.y - oldMousePos.getY());
		this->callOnMouseMove(deltaPt);
	}

	this->oldMousePos = Point(currentPt.x, currentPt.y);

	if (GetKeyboardState(keyStates)) //update keyStates
	{
		for (int i = 0; i < ARRAYSIZE(keyStates); i++)
		{
			// this->keyStates[i] & 0x80 checks whether a key has been pressed (regardless of whether it is toggled / untoggled)
			if (this->keyStates[i] & 0x80 && this->keyStates[i] != this->oldKeyStates[i])
			{
				if (VK_LBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - this->oldMousePos.getX(), currentPt.y - this->oldMousePos.getY());
					this->callOnLeftMouseDown(deltaPt);
				}
				else if (VK_RBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - this->oldMousePos.getX(), currentPt.y - this->oldMousePos.getY());
					this->callOnRightMouseDown(deltaPt);
				}
				else
					callOnKeyDown(i);
			}
			else if (this->keyStates[i] != this->oldKeyStates[i])
			{
				if (VK_LBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - this->oldMousePos.getX(), currentPt.y - this->oldMousePos.getY());
					this->callOnLeftMouseUp(deltaPt);
				}
				else if (VK_RBUTTON == i && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - this->oldMousePos.getX(), currentPt.y - this->oldMousePos.getY());
					this->callOnRightMouseUp(deltaPt);
				}
				else
					callOnKeyUp(i);
			}
		}

		//store current keys to old states
		::memcpy(this->oldKeyStates, this->keyStates, sizeof(unsigned char) * 256);
	}
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->keyStates); i++) {
		if (this->keyStates[i] & 0x80 && i == key) {
			return true;
		}
		else if (i == key) {
			return false;
		}
	}


	return false;
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->keyStates); i++) {
		if (!(this->keyStates[i] & 0x80) && i == key) {
			return true;
		}
		else if (i == key) {
			return false;
		}
	}

	return false;
}

void InputSystem::callOnKeyDown(int key)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onKeyDown(key);
	}
}

void InputSystem::callOnKeyUp(int key)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onKeyUp(key);
	}
}

void InputSystem::callOnMouseMove(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onMouseMove(deltaPt);
	}
}

void InputSystem::callOnLeftMouseDown(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onLeftMouseDown(deltaPt);
	}
}

void InputSystem::callOnLeftMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onLeftMouseUp(deltaPt);
	}
}

void InputSystem::callOnRightMouseDown(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onRightMouseDown(deltaPt);
	}
}

void InputSystem::callOnRightMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++) {
		this->inputListenerList[i]->onRightMouseUp(deltaPt);
	}
}