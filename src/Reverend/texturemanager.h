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
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
	void clearTextureMap();
	void clearFromTextureMap(std::string id);

	static TextureManager* getInstance()
	{
		if(instance_ == 0)
		{
			instance_ = new TextureManager();
			return instance_;
		}
		return instance_;
	} 

private:
	TextureManager() {}
	static TextureManager* instance_;
	std::map<std::string, SDL_Texture*> textureMap_;
};

#endif