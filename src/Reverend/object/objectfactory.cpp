#include "objectfactory.h"

std::map<std::string, Creator*> ObjectFactory::map_;

GameObject* ObjectFactory::create(std::string type, const LoaderParams* pParams) {
	return map_[type]->create(pParams);
}

void ObjectFactory::registerType(const std::string& type, Creator* creator) {
	map_[type] = creator;
}

GameObject *PlayerCreator::create( const LoaderParams* pParams )
{
	return new Player(pParams);
}

GameObject *EnemyCreator::create( const LoaderParams* pParams )
{
	return new Enemy(pParams);
}