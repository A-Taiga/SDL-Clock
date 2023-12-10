#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <concepts>
#include <limits>
#include <type_traits>
#include <cmath>
#include "angles.hpp"

#define WHITE 255,255,255,0
#define RED 255,0,0,0
#define CYAN 0,255,255,0
#define GREEN 0,255,0,0
#define PINK 255,0,255,0
#define BLACK 0,0,0,0

template<class T>
concept vecReq = requires {std::is_integral_v<T> || std::is_floating_point_v<T>;};

template<vecReq T>
class Vec2;
template<vecReq T>
class Vec3;

template <class T>
concept vecType = requires (T t)
{
	std::is_same_v<T, Vec2<decltype(t.x)>> 
	|| std::is_same_v<T, Vec3<decltype(t.x)>>;
};

template<class T>
concept AngleUnit = requires (T v)
{
	std::is_floating_point_v<decltype(v)> &&
	(
		std::is_same_v<T, angles::Degrees<decltype(v.val)>> ||
		 std::is_same_v<T,angles::Radians<decltype(v.val)>>
	);
};

template<AngleUnit T>
inline static decltype(auto) cosine(T value);

template<AngleUnit T>
inline static decltype(auto) sine(T value);


template<vecReq T>
class Vec2
{
	private:
	T radians(T degree) { return degree * (M_PI/180); }
	T degrees(T radian) { return radian * (180/M_PI); }
	
	public:
	T x,y;
	T cx,cy;
	Vec2(T _x = 0, T _y = 0, T _cx = 0, T _cy = 0)
	: x(_x), y(_y), cx(_cx), cy(_cy){}

	void rotate(angles::Degrees<T> angle, const Vec2<T>& base);
	void rotate(angles::Degrees<T> angle);
};

template<vecReq T>
class Vec3
{
	public:
	T x,y,z;
	T cx,cy,cz;
};


template<vecReq T>
void Vec2<T>::rotate(angles::Degrees<T> angle, const Vec2<T>& base)
{
	T c = cosine(static_cast<angles::Radians<T>>(angle));
	T s = sine(static_cast<angles::Radians<T>>(angle));

	T translatedX = base.x - cx;
	T translatedY = base.y - cy;

	T resultX = translatedX * c - translatedY * s;
	T resultY = translatedX * s + translatedY * c;

	resultX += cx;
	resultY += cy;

	x = resultX;
	y = resultY;
}

template<vecReq T>
void Vec2<T>::rotate(angles::Degrees<T> angle)
{
	auto c = cosine(static_cast<angles::Radians<T>>(angle));
	auto s = sine(static_cast<angles::Radians<T>>(angle));

	T translatedX = x - cx;
	T translatedY = y - cy;

	T resultX = translatedX * c - translatedY * s;
	T resultY = translatedX * s + translatedY * c;

	resultX += cx;
	resultY += cy;

	x = resultX;
	y = resultY;
}

inline const char* week_day(int n)
{
	switch(n)
	{
		case 0: return "Sun"; break;
		case 1: return "Mon"; break;
		case 2: return "Tue"; break;
		case 3: return "Wed"; break;
		case 4: return "Thu"; break;
		case 5: return "Fri"; break;
		case 6: return "Sat"; break;
		default:return "000"; break;
	}
}
inline const char* month(int n)
{
	switch(n)
	{
		case 0: return "Jan"; break; 
		case 1: return "Feb"; break; 
		case 2: return "Mar"; break;
		case 3: return "Apr"; break;
		case 4: return "May"; break;
		case 5: return "June"; break;
		case 6: return "July"; break;
		case 7: return "Aug"; break;
		case 8: return "Sept"; break;
		case 9: return "Oct"; break;
		case 10: return "Nov"; break;
		case 11: return "Dec"; break;
		default:return  "0000"; break;
	}
}
inline int to12H(int h)
{
	if(h > 12)
	{
		int newH = h - 12;
		if(h == 0)
			return 12;
		return newH;
	}
	return h;
}

template<AngleUnit T>
inline static decltype(auto) cosine(T value) { return std::cos(value); }

template<AngleUnit T>
inline static decltype(auto) sine(T value) { return std::sin(value); }

#endif
