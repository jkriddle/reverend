#pragma once
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <map>

#include "player.h"
#include "enemy.h"

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
	static void clear();
private:
	static std::map<std::string, Creator*> ObjectFactory::map_;
};

#endif