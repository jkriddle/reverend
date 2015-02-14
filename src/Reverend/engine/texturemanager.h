#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
	bool load(const char* fileName, const char* id, SDL_Renderer* renderer);
	void draw(const char* id, int x, int y, int width, int height, SDL_Renderer* pRenderer);
	void drawFrame(const char* id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer*pRendere);
	void drawTile(const char* id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
	void clearTextureMap();
	void clearFromTextureMap(const char* id);

	static TextureManager& getInstance()
	{
		static TextureManager instance_;
		return instance_;
	} 

private:
	TextureManager() {}
	~TextureManager() {
	}
	std::map<const std::string, SDL_Texture*> textureMap_;
};

#endif