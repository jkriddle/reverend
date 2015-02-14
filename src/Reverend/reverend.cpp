#include "reverend.h"
#include "engine/texturemanager.h"
#include "engine/soundmanager.h"
#include "engine/camera.h"

void Reverend::load() {
	// Setup camera
	CameraManager::mainCamera = new Camera(getScreenWidth(), getScreenHeight());

	// Load Textures
	// TODO - move this to PlayState once we have the whole texture management/component renderer figured out.
	TextureManager::getInstance().load("assets/textures/player.png", "player", getRenderer());
	TextureManager::getInstance().load("assets/textures/enemy.png", "enemy", getRenderer());
	TextureManager::getInstance().load("assets/textures/water.png", "water", getRenderer());
	TextureManager::getInstance().load("assets/textures/shallows.png", "shallows", getRenderer());
	TextureManager::getInstance().load("assets/textures/sand.png", "sand", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass.png", "grass", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-n.png", "grass-n", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-ne.png", "grass-ne", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-e.png", "grass-e", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-se.png", "grass-se", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-s.png", "grass-s", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-sw.png", "grass-sw", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-w.png", "grass-w", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/grass-nw.png", "grass-nw", getRenderer());
	TextureManager::getInstance().load("assets/textures/terrain/dirt.png", "dirt", getRenderer());
	TextureManager::getInstance().load("assets/textures/rock.png", "rock", getRenderer());
	TextureManager::getInstance().load("assets/textures/snow.png", "snow", getRenderer());
	SoundManager::getInstance().load("assets/sounds/fast_swipe.wav", "short_swipe", SoundType::SOUND_SFX);
}

void Reverend::close() {
	TextureManager::getInstance().clearFromTextureMap("player");
	TextureManager::getInstance().clearFromTextureMap("enemy");
	TextureManager::getInstance().clearFromTextureMap("water");
	TextureManager::getInstance().clearFromTextureMap("shallows");
	TextureManager::getInstance().clearFromTextureMap("sand");
	TextureManager::getInstance().clearFromTextureMap("grass");
	TextureManager::getInstance().clearFromTextureMap("dirt");
	TextureManager::getInstance().clearFromTextureMap("rock");
	TextureManager::getInstance().clearFromTextureMap("snow");
	CameraManager::cleanup();
}