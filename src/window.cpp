#include "window.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"

Window::Window(int _width, int _height, const char* windowName)
: renderer(std::make_shared<SDL_Renderer*>())
, width(_width)
, height(_height)
, running(true)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL init failure " << SDL_GetError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
	if(!window)
	{
		std::cout << "window is null " << SDL_GetError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	renderer = std::make_shared<SDL_Renderer*>(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
	if(!renderer.get())
	{
		std::cout << "renderer is null " << SDL_GetError() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	puts("SDL window destoryed");
	SDL_Quit();
}

void Window::update()
{
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
	SDL_RenderPresent(*renderer);
	SDL_RenderClear(*renderer);
}

bool Window::is_running()
{
	return running;
}

std::shared_ptr<SDL_Renderer*> Window::get_renderer()
{
	return renderer;
}

int Window::get_window_index()
{
	return SDL_GetWindowDisplayIndex(window);
}

Vec2<int> Window::size()
{
	int w,h;
	SDL_GetWindowSizeInPixels(window,&w,&h);
	return {w,h};
}

void Window::poll_events()
{
	SDL_Event event;
	while(SDL_PollEvent(&event) > 0)
	{
		switch(event.type)
		{
			case SDL_QUIT: running = false;
			break;
		}
	}
}



