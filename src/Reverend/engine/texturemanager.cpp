#include "texturemanager.h"

bool TextureManager::load(const std::string& fileName, const std::string& id, SDL_Renderer* pRenderer) {
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
	if(tempSurface == 0) {
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	// everything went ok, add the texture to our list
	if (pTexture != 0) {
		textureMap_[id] = pTexture;
		return true;
	}
	
	// reaching here means something went wrong
	return false;
}

void TextureManager::draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, textureMap_[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(const std::string& id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, textureMap_[id], &srcRect, &destRect, 0, 0, flip);
	//SDL_RenderDrawRect(pRenderer, &destRect);
}

void TextureManager::drawTile(const std::string& id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopyEx(pRenderer, textureMap_[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearTextureMap()
{
    textureMap_.clear();
}

void TextureManager::clearFromTextureMap(const std::string& id)
{
    textureMap_.erase(id);
}