#pragma once

#include <optional>
#include <string_view>
#include <type_traits>
#include <stdexcept>

#include "System/Exception.hpp"

void _HandleTryException(std::string_view name, int ex);
void _HandleTryException(std::string_view name, const std::exception& ex);
void _HandleTryException(std::string_view name, const Il2CppExceptionWrapper& wrapper);
void _HandleTryException(std::string_view name);

template <typename TFunc, typename TRet = std::invoke_result_t<TFunc>>
std::optional<TRet> TryGuarded(std::string_view name, TFunc&& func)
{
	try
	{
		return func();
	}
	catch (int ex)
	{
		_HandleTryException(name, ex);
	}
	catch (const std::exception& ex)
	{
		_HandleTryException(name, ex);
	}
	catch (const Il2CppExceptionWrapper& wrapper)
	{
		_HandleTryException(name, wrapper);
	}
	catch (...)
	{
		_HandleTryException(name);
	}

	return std::nullopt;
}
