#include "ActionHistory.h"

#include "ActionMomento.h"
#include "EditorAction.h"
ActionHistory* ActionHistory::sharedInstance = nullptr;
ActionHistory* ActionHistory::getInstance()
{
}

void ActionHistory::initialize()
{
}

void ActionHistory::destroy()
{
}

void ActionHistory::startRecordAction(AGameObject* gameObject)
{
}

void ActionHistory::endRecordAction(AGameObject* gameObject)
{
}

bool ActionHistory::hasRemainingUndoActions()
{
}

bool ActionHistory::hasRemainingRedoActions()
{
}

EditorAction* ActionHistory::undoAction()
{
}

EditorAction* ActionHistory::redoAction()
{
}

void ActionHistory::clear()
{
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}
