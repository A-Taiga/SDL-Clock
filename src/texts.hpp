#ifndef TEXTS_HPP
#define TEXTS_HPP

#include "text.hpp"
#include "utility.hpp"
#include <memory>


template<vecReq T>
class Texts
{
	public:
	Text text;
	Vec2<T> pos;
	Texts(int fontSize, std::shared_ptr<SDL_Renderer*> renderer, T x = 0, T y = 0, T cx = 0, T cy = 0)
	: text(fontSize, renderer)
	, pos(x,y,cx,cy)
	{}
};

#endif
