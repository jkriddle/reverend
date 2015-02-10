#include "../engine/component/component.h"
#include "../engine/input.h"
#include "../engine/gameobject.h"

class PlayerInput : public Component {

public:
	PlayerInput(GameObject& parent) : speed_(3), Component(parent) {
	}

	void update();
	void receiveMessage(Message* message) {}

private:
	void handleKeyboardInput();
	int speed_;

};