#include "input.h"

#include <iostream>

void Input::assignActionToInputPressed(int input, int action)
{
	//Remap input if it is already assigned
	if (inputs_pressed.count(input))
	{
		inputs_pressed[input] = action;
		return;
	}

	//First time mapping
	inputs_pressed.insert(std::pair<int, int>(input, action));
}

void Input::assignActionToInputReleased(int input, int action)
{
	//Remap input if it is already assigned
	if (inputs_released.count(input))
	{
		inputs_released[input] = action;
		return;
	}

	//First time mapping
	inputs_released.insert(std::pair<int, int>(input, action));
}

void Input::assignCallbackToAction(int action, std::function<void()> callback)
{
	//Add action if not already present
	if (callbacks.count(action) == 0)
	{
		callbacks[action] = std::vector<std::function<void()>>();
	}

	//Add the new callback to the mapped vector of callbacks
	callbacks[action].push_back(callback);
}

void Input::removeCallbacksFromAction(int action)
{
	//return if action wasn't registered yet
	if (callbacks.count(action) == 0) return;
	callbacks[action].clear();
}

void Input::processPressed(int input)
{
	//Get the mapped action from the input
	int action = inputs_pressed[input];

	//Do nothing on unassigned input
	if (action == 0) return;

	//Then run all of the associated callbacks
	for (std::function<void()> callback : callbacks[action])
	{
		callback();
	}
}

void Input::processReleased(int input)
{
	//Get the mapped action from the input
	int action = inputs_released[input];

	//Do nothing on unassigned input
	if (action == 0) return;

	//Then run all of the associated callbacks
	for (std::function<void()> callback : callbacks[action])
	{
		callback();
	}
}


