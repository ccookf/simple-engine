#ifndef INPUT_H
#define INPUT_H

#include <functional>
#include <map>
#include <vector>

/**
 * The simplified input system will add more overhead to anything requiring a 
 * key to be held, but the majority of anticipated inputs will be keydown events
 *
 * To avoid storing state for up/down/left/right we'll do indepedent velocity
 * changes without conditional logic. However, this will open up bugs regarding
 * held/released keys during loading or when alt tabbing the game. Furthermore,
 * this will limit bindings per action for held keys.
 * Eg.  W or Up for Action_Up_Pressed will cause bugs, but
 * 		F or E or for things like cooldown abilities is fine
 */
enum InputActions
{
	//No action = 0
	Action_Up_Pressed = 1,
	Action_Up_Released,
	Action_Down_Pressed,
	Action_Down_Released,
	Action_Left_Pressed,
	Action_Left_Released,
	Action_Right_Pressed,
	Action_Right_Released
};

/**
 * Straightforward, I used vector of callback functions to leave room for
 * shenanigans with input reading or multiple objects responding to input
 *
 * The whole point of this class is decouple raw input from events and
 * allow easy extension for key remapping in larger projects.
 */
class Input
{
public:
	void assignActionToInputPressed(int input, int action);
	void assignActionToInputReleased(int input, int action);
	void assignCallbackToAction(int action, std::function<void()> callback);
	void processPressed(int input);
	void processReleased(int input);

private:
	std::map<int, int> inputs_pressed;
	std::map<int, int> inputs_released;
	std::map<int, std::vector<std::function<void()>>> callbacks;
};

#endif
