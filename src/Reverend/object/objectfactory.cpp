#include "objectfactory.h"

std::map<std::string, Creator*> ObjectFactory::map_;

SDLGameObject* ObjectFactory::create(std::string type, const LoaderParams* pParams) {
	return map_[type]->create(pParams);
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