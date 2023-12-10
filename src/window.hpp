
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_video.h"
#include <memory>
#include "utility.hpp"

class Window
{
	private:
	std::shared_ptr<SDL_Renderer*> renderer;
	SDL_Window* window;
	int width, height;
	bool running;

	public:
	Window(int _width, int _height, const char* windowName);
	~Window();
	void update();
	bool is_running();
	std::shared_ptr<SDL_Renderer*> get_renderer();
	int get_window_index();
	Vec2<int> size();
	void poll_events();
	
	template<vecType T>
	void draw_line(const T& v1, const T& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	template<vecType T>
	void draw_line(const T&& v1, const T&& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	template<vecType T>
	void draw_line(const T& v1, const T&& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	template<vecType T>
	void draw_line(const T&& v1, const T& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	template<vecType T>
	void draw_vector(const T& v, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	template<vecType T>
	void draw_vector(const T&& v,Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
};


template<vecType T>
void Window::draw_line(const T& v1, const T& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_SetRenderDrawColor(*renderer, r,g,b,a);

	if constexpr ( std::is_floating_point_v< decltype( v1.x ) > )
		SDL_RenderDrawLineF( *renderer, v1.x, v1.y, v2.x, v2.y );

	else if constexpr ( std::is_integral_v< decltype( v1.x )> )
		SDL_RenderDrawLine( *renderer, v1.x, v1.x, v2.x, v2.y );
}
template<vecType T>
void Window::draw_line(const T&& v1, const T&& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_SetRenderDrawColor(*renderer, r,g,b,a);

	if constexpr( std::is_floating_point_v< decltype( v1.x ) > )
		SDL_RenderDrawLineF( *renderer, v1.x, v1.y, v2.x, v2.y );

	else if constexpr( std::is_integral_v< decltype( v1.x )> )
		SDL_RenderDrawLine( *renderer, v1.x, v1.x, v2.x, v2.y );
}

template<vecType T>
void Window::draw_line(const T& v1, const T&& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_SetRenderDrawColor(*renderer, r,g,b,a);

	if constexpr( std::is_floating_point_v< decltype( v1.x ) > )
		SDL_RenderDrawLineF( *renderer, v1.x, v1.y, v2.x, v2.y );

	else if constexpr( std::is_integral_v< decltype( v1.x )> )
		SDL_RenderDrawLine( *renderer, v1.x, v1.x, v2.x, v2.y );
}

template<vecType T>
void Window::draw_line(const T&& v1, const T& v2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_SetRenderDrawColor(*renderer, r,g,b,a);

	if constexpr( std::is_floating_point_v< decltype( v1.x ) > )
		SDL_RenderDrawLineF( *renderer, v1.x, v1.y, v2.x, v2.y );

	else if constexpr( std::is_integral_v< decltype( v1.x )> )
		SDL_RenderDrawLine( *renderer, v1.x, v1.x, v2.x, v2.y );
}

template<vecType T>
void Window::draw_vector(const T& v, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_SetRenderDrawColor(*renderer, r,g,b,a);

	if constexpr( std::is_floating_point_v< decltype( v.x ) > )
		SDL_RenderDrawLineF( *renderer, v.x, v.y, v.cx, v.cy );

	else if constexpr( std::is_integral_v< decltype( v.x )> )
		SDL_RenderDrawLine( *renderer, v.x, v.x, v.cx, v.cy );

}

template<vecType T>
void Window::draw_vector(const T&& v,Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_SetRenderDrawColor(*renderer, r,g,b,a);

	if constexpr( std::is_floating_point_v< decltype( v.x ) > )
		SDL_RenderDrawLineF( *renderer, v.x, v.y, v.cx, v.cy );

	else if constexpr( std::is_integral_v< decltype( v.x )> )
		SDL_RenderDrawLine( *renderer, v.x, v.x, v.cx, v.cy );
}
#endif