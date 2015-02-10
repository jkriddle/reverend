#pragma once
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <map>
#include <vector>
#include "../actors/player.h"
#include "../actors/enemy.h"

// Base class
 
// Or use a macro like I did:
//map->register( "Player", new PlayerCreator( ) );
//REGISTER_CREATOR( RedBlock );


class Creator
{
public:
	virtual SDLGameObject *create( const LoaderParams* pParams ) = 0;
};

class PlayerCreator : public Creator
{
	virtual SDLGameObject *create( const LoaderParams* pParams );
};

class EnemyCreator : public Creator
{
	virtual SDLGameObject *create( const LoaderParams* pParams );
};

class ObjectFactory {
public:
	static SDLGameObject* create(std::string type, const LoaderParams* pParams);
	static void registerType(const std::string& type, Creator* creator);
	static std::vector<SDLGameObject*> getObjects();
	static void clear();
private:
	static std::map<std::string, Creator*> ObjectFactory::map_;
	static std::vector<SDLGameObject*> ObjectFactory::objects_;
};

#endif