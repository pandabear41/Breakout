#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include <string>

#ifdef WIN32
    #include <SDL.h>
    #include <SDL_ttf.h>
    #include <SDL_image.h>
    #include <SDL_gfxPrimitives.h>
#else
    #include <SDL/SDL.h>
    #include <SDL/SDL_ttf.h>
    #include <SDL/SDL_image.h>
    #include <SDL/SDL_gfxPrimitives.h>
#endif

#include "Setting.h"

class Draw {
public:
    Draw();
    virtual ~Draw();

    // Some loading funcs.
    static SDL_Surface* loadBMP(const std::string file);
	static SDL_Surface* loadIMG(const std::string file);


    static void drawText(SDL_Surface* surface, const std::string text,
                        SDL_Color color, const int x = 0, const int y = 0, const int size =
                        30, const int alpha = 255);
    static void drawText(SDL_Surface* surface, const std::string text, SDL_Color color, const char* fontfile,
                         const int x = 0, const int y = 0, const int size = 30, const int alpha = 255);

    static void filledRect(SDL_Surface* surface, int x, int y, int w, int h, int color=0xFFFFFF);

    static bool drawSurface(SDL_Surface* dest, SDL_Surface* src, int x, int y);
    static bool drawSurface(SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int w, int h);

	static bool setTransparent(SDL_Surface* dest, int r, int g, int b);
};


#endif // DRAW_H_INCLUDED
