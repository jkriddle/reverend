#include "texturemanager.h"

bool TextureManager::load(const char* fileName, const char* id, SDL_Renderer* pRenderer) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
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

bool TextureManager::loadFont(const char* fileName, const char* id, int size) {
	TTF_Font* ttf = TTF_OpenFont(fileName, size); //this opens a font style and sets a size
	fontMap_[id] = ttf;
	return true;
}

void TextureManager::draw(const char* id, int x, int y, int width, int height, SDL_Renderer* pRenderer) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopy(pRenderer, textureMap_[id], &srcRect, &destRect);
}

void TextureManager::drawFrame(const char* id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopy(pRenderer, textureMap_[id], &srcRect, &destRect);
	//SDL_RenderDrawRect(pRenderer, &destRect);
}

void TextureManager::drawTile(const char* id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    
    SDL_RenderCopy(pRenderer, textureMap_[id], &srcRect, &destRect);
}

void TextureManager::drawText(const char* id, const char* text, SDL_Color color, int x, int y, int w, int h, SDL_Renderer* renderer) {

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fontMap_[id], text, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect messageRect; 
	messageRect.x = x;  
	messageRect.y = y;
	messageRect.w = w; 
	messageRect.h = h; 

	SDL_RenderCopy(renderer, message, NULL, &messageRect); 

}

void TextureManager::clearTextureMap()
{
    textureMap_.clear();
}

void TextureManager::clearFromTextureMap(const char* id)
{
    textureMap_.erase(id);
}