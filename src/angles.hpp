#ifndef ANGLES_HPP
#define ANGLES_HPP

#include <concepts>
#include <type_traits>
#include <cmath>
#include <utility>
#include <concepts>


template<class T>
concept AngleType = std::is_floating_point_v<T> || std::is_integral_v<T>;

namespace angles
{
	template<AngleType T>
	struct Degrees;

	template<AngleType T>
	struct ArcMinutes;

	template<AngleType T>
	struct Radians
	{
		public:
		T val;
		constexpr Radians() = default;
		constexpr Radians(T v);
		// cast from degrees
		constexpr Radians(const Degrees<T>& from) noexcept;
		// copy constructor
		constexpr Radians(const Radians<T>&) = default;
		// move constructor
		constexpr Radians(Radians<T>&&) = default;
		// copy assignment
		constexpr Radians<T>& operator = (const Radians<T>&) = default;
		// move assignment
		constexpr Radians<T>& operator = (Radians<T>&&) = default;

		constexpr operator Degrees<T>() const { return Degrees<T>(); }
		
		constexpr operator T() { return val; }

	};

	template<AngleType T>
	struct Degrees
	{
		public:
		T val;

		constexpr Degrees() = default;

		constexpr Degrees(T v);
		// cast from Radians
		constexpr Degrees(const Radians<T>& from) noexcept;
		// cast from ArcMinutes
		constexpr Degrees(const ArcMinutes<T>& from) noexcept;
		// copy constructor
		constexpr Degrees(const Degrees<T>& other) = default; 
		// move constructor
		constexpr Degrees(Degrees<T>&& other) = default;
		// copy assignment
		constexpr Degrees<T>& operator = (const Degrees<T>& other) = default;
		 // move assignment
		constexpr Degrees<T>& operator = (Degrees<T>&& other) = default;

		constexpr operator Radians<T>() const { return Radians<T>(); }
		constexpr operator ArcMinutes<T>() const { return ArcMinutes<T>(); }

		constexpr operator T(){return val;}
	};
	/* not fully implemented yet */
	template<AngleType T>
	struct ArcMinutes
	{
		public:
		T val;

		constexpr ArcMinutes() = default;
		constexpr ArcMinutes(T v);
		// cast from Degrees
		constexpr ArcMinutes(const Degrees<T>& from) noexcept;
		// copy constructor
		constexpr ArcMinutes(const ArcMinutes<T>& other) = default;
		// move constructor
		constexpr ArcMinutes(ArcMinutes<T>&& other) = default;
		// copy assignment
		constexpr ArcMinutes<T>& operator = (const ArcMinutes<T>& other) = default;
		 // move assignment
		constexpr ArcMinutes<T>& operator = (ArcMinutes<T>&& other) = default;

		
		constexpr operator Degrees<T>() const { return Degrees<T>(); }
		constexpr operator T(){return val;}

	};
}

template<AngleType T>
constexpr angles::Radians<T>::Radians(T v)
: val (v)
{}

template<AngleType T>
constexpr angles::Radians<T>::Radians(const Degrees<T>& from) noexcept
: val (from.val * (M_PI/180))
{}

/* Degrees ================================================ */

template<AngleType T>
constexpr angles::Degrees<T>::Degrees(T v)
: val (v)
{}

// convert from Radians
template<AngleType T>
constexpr angles::Degrees<T>::Degrees(const Radians<T>& from) noexcept
:val (from.val * (180/M_PI))
{}

// convert from ArcMinutes
template<AngleType T>
constexpr angles::Degrees<T>::Degrees(const ArcMinutes<T>& from) noexcept
:val (from.val / 60)
{}

/* ArcMinutes ================================================ */

template<AngleType T>
constexpr angles::ArcMinutes<T>::ArcMinutes(T v)
: val (v)
{}

// cast from Degrees
template<AngleType T>
constexpr angles::ArcMinutes<T>::ArcMinutes(const Degrees<T>& from) noexcept
: val (from.val * 60)
{}


template<class T>
concept castType = requires (T v)
{
	std::is_same_v<T, angles::Degrees<decltype(v.val)>>
	|| std::is_same_v<T, angles::Radians<decltype(v.val)>>;
};

template<castType T>
T constexpr cast(auto v)
{
	if constexpr (std::is_same_v<decltype(v), T>)
	{
		return v;
	}
	if constexpr (std::is_same_v<decltype(v), angles::Degrees<decltype(v.val)>>)
	{
		return (T(v.val * (M_PI/180)));
	}
	else if constexpr ( std::is_same_v<decltype(v), angles::Radians<decltype(v.val)>> )
	{
		return (T(v.val * (180/M_PI)));
	}
}

consteval auto operator "" _degrees(unsigned long long v)
{
	return angles::Degrees<int>(static_cast<int>(v));
}

consteval auto operator "" _degrees(long double v)
{
	return angles::Degrees<double>(static_cast<double>(v));
}

consteval auto operator "" _degreesF(long double v)
{
	return angles::Degrees<float>(static_cast<float>(v));
}

consteval auto operator "" _radians(long double v)
{
	return angles::Radians<double>(static_cast<double>(v));
}

consteval auto operator "" _radiansF(long double v)
{
	return angles::Radians<float>(static_cast<float>(v));
}

consteval auto operator "" _arcmin(long double v)
{
	return angles::ArcMinutes<double>(static_cast<double>(v));
}

#endif