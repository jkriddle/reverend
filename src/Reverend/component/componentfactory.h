#pragma once
#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "component.h"
#include <string>
#include <vector>
#include <stdexcept>

class ComponentFactory {

public:
	
	template <typename T>
	T* create(GameObject& parent) {
		T o = new T(parent);
		return o;
	}

	template <typename T>
	T* getComponent() {
		for(Component* c : components_) {
			T* cType = dynamic_cast<T*>(c);
			if (cType != nullptr) return cType;
		}
		return nullptr;
	}
	
	template <typename T>
	T* getComponent(std::string name) {
		throw std::logic_error("Not implemented yet.");
	}
	
	template <typename T>
	std::vector<T*> getComponents() {
		std::vector<T*> matching;
		for(Component* c : components_) {
			T* cType = dynamic_cast<T*>(c);
			if (cType != nullptr) {
				matching.push_back(cType);
			}
		}
		return matching;
	}


};

#endif;