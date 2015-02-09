#include "objectfactory.h"

std::map<std::string, Creator*> ObjectFactory::map_;
std::vector<SDLGameObject*> ObjectFactory::objects_;

SDLGameObject* ObjectFactory::create(std::string type, const LoaderParams* pParams) {
	objects_.push_back(map_[type]->create(pParams));
	return objects_.back();
}

std::vector<SDLGameObject*> ObjectFactory::getObjects() {
	return objects_;
}

void ObjectFactory::registerType(const std::string& type, Creator* creator) {
	map_[type] = creator;
}

void ObjectFactory::clear() {
	map_.clear();
}

SDLGameObject *PlayerCreator::create( const LoaderParams* pParams )
{
	return new Player(pParams);
}

SDLGameObject *EnemyCreator::create( const LoaderParams* pParams )
{
	return new Enemy(pParams);
}