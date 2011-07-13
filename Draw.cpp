#include "Draw.h"

using namespace std;

Draw::Draw() {
}

Draw::~Draw() {
}

SDL_Surface* Draw::loadBMP(const string file) {
	SDL_Surface* temp = NULL;
	SDL_Surface* optimised = NULL;

	if((temp = SDL_LoadBMP(file.c_str())) == NULL) {
		return NULL;
	}
	optimised = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	return optimised;
}

SDL_Surface* Draw::loadIMG(const string file) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load(file.c_str());

  if(loadedImage != NULL )
  {
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);

    if(optimizedImage != NULL )
    {
      Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF, 0xFF);
      SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
    }
  }

  return optimizedImage;
}

void Draw::filledRect(SDL_Surface* surface, int x, int y, int w, int h, int color) {
    SDL_Rect rect = {x,y,w,h};
    SDL_FillRect(surface, &rect, color);
}

void Draw::drawText(SDL_Surface* surface, const string text, SDL_Color color, const char* fontfile, const int x, const int y, const int size, const int alpha) {
    TTF_Init();
    // Load font
    TTF_Font *font = TTF_OpenFont(fontfile, size);
    // Set font, text and color
    SDL_Surface *surfaceText;
    if (alpha < 255) {
        surfaceText = TTF_RenderText_Solid(font, text.c_str(), color);
    } else {
        surfaceText = TTF_RenderText_Blended(font, text.c_str(), color);
    }
    // Set position
    SDL_Rect rectText = { x, y, 0, 0 };
    // Set alpha
    if (alpha < 255) {
        SDL_SetAlpha(surfaceText, SDL_RLEACCEL | SDL_SRCALPHA, alpha);
    }
    // Set to surface
    SDL_BlitSurface(surfaceText, NULL, surface, &rectText);
    SDL_FreeSurface(surfaceText);
    TTF_CloseFont(font);
}

void Draw::drawText(SDL_Surface* surface, const string text, SDL_Color color,
                const int x, const int y, const int size, const int alpha) {
    Draw::drawText(surface, text, color, Setting::FONT, x, y, size, alpha);
}

bool Draw::drawSurface(SDL_Surface* dest, SDL_Surface* src, int x, int y) {
	if (src == NULL || dest == NULL) {
		return false;
	}

	SDL_Rect destLoc;

	destLoc.x = x;
	destLoc.y = y;

	SDL_BlitSurface(src, NULL, dest, &destLoc);

	return true;
}

bool Draw::drawSurface(SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int w, int h) {
	if (src == NULL || dest == NULL) {
		return false;
	}

	SDL_Rect destLoc;

	destLoc.x = x;
	destLoc.y = y;

	SDL_Rect srcLoc;

	srcLoc.x = x2;
	srcLoc.y = y2;
	srcLoc.w = w;
	srcLoc.h = h;

	SDL_BlitSurface(src, &srcLoc, dest, &destLoc);

	return true;
}

bool Draw::setTransparent(SDL_Surface* dest, int r, int g, int b) {
	if(dest == NULL) {
		return false;
	}

	SDL_SetColorKey(dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(dest->format, r, g, b));

	return true;
}




