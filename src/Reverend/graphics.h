#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL\SDL_render.h>
#include "gameobject.h"
//#include "component/componentfactory.h"
//#include "component/cameracomponent.h"

class Graphics {
public:
	void static render(GameObject* o, SDL_Renderer* renderer);
private:
	/*CameraComponent* getCamera() {
		if (mainCamera_ == nullptr) {
			// find camera component
			//mainCamera_ = ComponentFactory::getComponent<CameraComponent>();
		}
		return mainCamera_;
	}

	CameraComponent* mainCamera_;*/
};

#endif