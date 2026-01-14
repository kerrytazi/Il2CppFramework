#pragma once

#include <string_view>

namespace cs
{

enum class Color
{
	Default,
	White,
	Black,
	Gray,
	Red,
	Green,
	Blue,
	Yellow,
	Orange,
	Pink,
	Cyan,
	Purple,
};

template <typename T>
struct Colored
{
	T value;
	Color color = Color::Default;
};

using ColoredString = Colored<std::string_view>;

template <typename T> constexpr Colored<T> Default(T _value) { return Colored<T>{ _value, Color::Default }; };
template <typename T> constexpr Colored<T> White(T _value) { return Colored<T>{ _value, Color::White }; };
template <typename T> constexpr Colored<T> Black(T _value) { return Colored<T>{ _value, Color::Black }; };
template <typename T> constexpr Colored<T> Gray(T _value) { return Colored<T>{ _value, Color::Gray }; };
template <typename T> constexpr Colored<T> Red(T _value) { return Colored<T>{ _value, Color::Red }; };
template <typename T> constexpr Colored<T> Green(T _value) { return Colored<T>{ _value, Color::Green }; };
template <typename T> constexpr Colored<T> Blue(T _value) { return Colored<T>{ _value, Color::Blue }; };
template <typename T> constexpr Colored<T> Yellow(T _value) { return Colored<T>{ _value, Color::Yellow }; };
template <typename T> constexpr Colored<T> Orange(T _value) { return Colored<T>{ _value, Color::Orange }; };
template <typename T> constexpr Colored<T> Pink(T _value) { return Colored<T>{ _value, Color::Pink }; };
template <typename T> constexpr Colored<T> Cyan(T _value) { return Colored<T>{ _value, Color::Cyan }; };
template <typename T> constexpr Colored<T> Purple(T _value) { return Colored<T>{ _value, Color::Purple }; };

template <typename T> constexpr const T& UnrapColored(const T& val) { return val; }
template <typename T> constexpr const T& UnrapColored(const cs::Colored<T>& colored) { return colored.value; }

template <typename T> constexpr cs::Color UnrapColor(const T& val) { return cs::Color::Default; }
template <typename T> constexpr cs::Color UnrapColor(const cs::Colored<T>& colored) { return colored.color; }

} // namespace cs
