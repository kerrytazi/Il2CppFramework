#pragma once

#include "il2cpp/Method.hpp"
#include "common/Templates.hpp"

#include "il2cpp.hpp"

#include <cassert>

namespace il2cpp
{

template <typename TFunc, typename TFinder>
struct MethodFinderOnce
{
	using pointer = typename templates::func<TFunc>::pointer;
	static inline pointer ptr = nullptr;

	static pointer Find()
	{
		if (!ptr) [[unlikely]]
		{
			auto game_method = TFinder{}();
			assert(game_method);
			ptr = game_method->template GetMethodPointer<TFunc>();
			assert(ptr);
		}

		return ptr;
	}

	static pointer FindICall()
	{
		if (!ptr) [[unlikely]]
		{
			ptr = (pointer)TFinder{}();
			assert(ptr);
		}

		return ptr;
	}
};

template <typename TFunc, typename TFinder>
auto FindMethodOnce()
{
	return MethodFinderOnce<TFunc, TFinder>::Find();
}

template <typename TFunc, typename TFinder>
auto FindICallMethodOnce()
{
	return MethodFinderOnce<TFunc, TFinder>::FindICall();
}

} // namespace il2cpp
