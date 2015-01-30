#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
	bool load(std::string fileName, std::string id, SDL_Renderer* renderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer*pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static TextureManager* Instance()
	{
		if(instance_ == 0)
		{
			instance_ = new TextureManager();
			return instance_;
		}
		return instance_;
	} 

private:
	TextureManager() {};
	std::map<std::string, SDL_Texture*> textureMap_;
	static TextureManager* instance_;
};

#endif