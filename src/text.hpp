#ifndef TEXT_HPP
#define TEXT_HPP
#include <SDL2/SDL_ttf.h>
#include <limits>
#include <memory>
#include <string_view>
#include <string>
#include "utility.hpp"

class Text
{
	private:
	std::shared_ptr<SDL_Renderer*> renderer;
	SDL_Texture *text;
	TTF_Font* font;
	std::string str;

	public:
	Text(int size,std::shared_ptr<SDL_Renderer*> _renderer);
	void renderText(std::string_view t, float _x, float _y);
	void set_text(std::string&& s);
	void renderText(float _x, float _y);

};

#endif