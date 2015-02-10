#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
class Component;
class GameObject;

class Object {

public:
	
	template <typename T>
	static T* create() {
		gameObjects_.push_back(new T());
		return (T*)gameObjects_.back();
	}

	template <typename T>
	static std::vector<T*> getObjects() {
		std::vector<T*> matching;
		for(Component* c : components_) {
			T* cType = dynamic_cast<T*>(c);
			if (cType != nullptr) {
				matching.push_back(cType);
			}
		}
		return matching;
	}
	
	static std::vector<GameObject*> getObjects() {
		return Object::gameObjects_;
	}

private:
	static std::vector<GameObject*> gameObjects_;

};



#endif;