#include "text.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include <cstdlib>
#include <iostream>


Text::Text(int size, std::shared_ptr<SDL_Renderer*> _renderer)
: renderer(_renderer)
{
	if(TTF_Init() < 0)
	{
		std::cout << "ttf init error " << TTF_GetError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	font = TTF_OpenFont("unifont-15.1.04.otf", size);
	if(!font)
	{
		std::cout << "Failed to load font " << TTF_GetError() << std::endl;
	}
	
}
void Text::renderText(std::string_view t, float _x, float _y)
{

	SDL_Surface *textSurface;
	textSurface = TTF_RenderText_Solid(font, t.data(), {WHITE});
	text = SDL_CreateTextureFromSurface(*renderer, textSurface);
	SDL_FRect dest = { _x - ((float)textSurface->w/2), _y - ((float)textSurface->h/2) , (float)textSurface->w, (float)textSurface->h };
	SDL_RenderCopyF(*renderer, text, nullptr, &dest);

}
void Text::set_text(std::string&& s)
{
	str = std::move(s);
}

void Text::renderText(float _x, float _y)
{

	SDL_Surface *textSurface;

	textSurface = TTF_RenderText_Solid(font,str.c_str(), {WHITE});
	text = SDL_CreateTextureFromSurface(*renderer, textSurface);
	SDL_FRect dest = { _x - ((float)textSurface->w/2), _y - ((float)textSurface->h/2), (float)textSurface->w, (float)textSurface->h };
	SDL_RenderCopyF(*renderer, text, nullptr, &dest);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(text);

}
