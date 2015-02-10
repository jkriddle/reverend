#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
	bool load(const std::string& fileName, const std::string& id, SDL_Renderer* renderer);
	void draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(const std::string& id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer*pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(const std::string& id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
	void clearTextureMap();
	void clearFromTextureMap(const std::string& id);

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
	std::map<const std::string, SDL_Texture*> textureMap_;
};

#endif