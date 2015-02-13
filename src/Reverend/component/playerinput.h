#include "../engine/component/component.h"
#include "../engine/input.h"
#include "../engine/gameobject.h"
#include "../engine/component/animatedsprite.h"

class PlayerInput : public Component {

public:
	PlayerInput(GameObject* parent) : speed_(3), Component(parent) {
	}
	virtual void start();
	void update();
	void receiveMessage(Message* message) {}

private:
	void getWalkingDirection();
	void PlayerInput::updateForwardTexture();
	void handleKeyboardInput();
	int speed_;
	AnimatedSprite* sprite_;
};