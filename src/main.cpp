#include "window.hpp"
#include "text.hpp"
#include "utility.hpp"
#include "texts.hpp"
#include <cstdlib>
#include <type_traits>
#include <vector>
#include <time.h>

#define WIDTH 450
#define HEIGHT 450

template<vecReq T>
void set_minutes(std::vector<Texts<T>>& minutes, const Vec2<T>& center, T radius);
template<vecReq T>
void set_seconds(std::vector<Texts<T>>& seconds, const Vec2<T>& center, T radius);

int main()
{
	Window window(WIDTH,HEIGHT,"SDL Clock");
	Uint64 start, end;
	float elapsedMS;
	time_t now = time(0);
	struct tm *tm = nullptr;

	Texts<float> dayNight(50, window.get_renderer());
	Texts<float> weekDay(50, window.get_renderer());
	Texts<float> day(50, window.get_renderer());

	Vec2<float> center;
	Vec2<float> secondHandBase;
	Vec2<float> hourHandBase;
	Vec2<float> minutHandBase;

	Vec2<float> hourHand;
	Vec2<float> minuteHand;
	Vec2<float> secondHand;

	std::vector<Texts<float>> minutes(12, {50, window.get_renderer()});
	std::vector<Texts<float>> seconds(60, {30, window.get_renderer()});

	center =
	{
		static_cast<decltype(center.x)>(window.size().x / static_cast<decltype(center.x)>(2)),
		static_cast<decltype(center.x)>(window.size().y / static_cast<decltype(center.x)>(2)),
	};

	secondHandBase = {center.x, 50, center.x, center.y};
	hourHandBase = {center.x, 150, center.x, center.y};
	minutHandBase = {center.x, 60, center.x, center.y};

	hourHand = {0, 0,center.x, center.y};
	minuteHand = {0, 0, center.x, center.y};
	secondHand = {0, 0, center.x, center.y};

	set_minutes(minutes, center, (float)80.0);
	set_seconds(seconds, center, (float)30.0);

	while(window.is_running())
	{
		window.poll_events();
		start = SDL_GetPerformanceCounter();

		now = time(0);
		if ((tm = localtime (&now)) == nullptr) 
		{
			puts("TIME ERROR");
			std::exit(EXIT_FAILURE);
		}

		window.draw_vector(secondHand, RED);
		window.draw_vector(minuteHand, GREEN);
		window.draw_vector(hourHand, CYAN);

		hourHand.rotate(to12H(tm->tm_hour) * 30.f, hourHandBase);
		minuteHand.rotate(tm->tm_min * 6.f, minutHandBase);
		secondHand.rotate(tm->tm_sec * 6.f, secondHandBase);

		dayNight.text.renderText(tm->tm_hour < 12 ? "AM" : "PM", center.x , 200);
		weekDay.text.renderText(week_day(tm->tm_wday), center.x + 100, center.y);
		day.text.renderText(std::to_string(tm->tm_mday), center.x + 180, center.y);

		for(auto&& m : minutes)
			m.text.renderText(m.pos.x, m.pos.y);

		for(auto&& s : seconds)
			s.text.renderText(s.pos.x, s.pos.y);

		window.update();
		end = SDL_GetPerformanceCounter();
		elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(16.666f - elapsedMS));
	}
	return 0;
}

template<vecReq T>
void set_minutes(std::vector<Texts<T>>& minutes, const Vec2<T>& center, T radius)
{
	for(int i = 1; i <= static_cast<int>(minutes.size()); i++)
	{
		minutes[i-1].pos = {center.x, radius, center.x, center.y};
		minutes[i-1].text.set_text(std::to_string(i));
		minutes[i-1].pos.rotate(i * static_cast<decltype(radius)>(30));
	}
}

template<vecReq T>
void set_seconds(std::vector<Texts<T>>& seconds, const Vec2<T>& center, T radius)
{
	for(int i = 1; i <= static_cast<int>(seconds.size()); i++)
	{
		seconds[i-1].pos = {center.x, radius, center.x, center.y};
		seconds[i-1].text.set_text(std::to_string(i));
		seconds[i-1].pos.rotate(i * static_cast<decltype(radius)>(6));
	}
}


