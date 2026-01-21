#pragma once

#include <optional>
#include <string_view>
#include <type_traits>
#include <excpt.h>

extern int _FilterSEHException(std::string_view name, unsigned long code, struct _EXCEPTION_POINTERS* pointers);

template <typename TFunc, typename TRet = std::invoke_result_t<TFunc>>
std::optional<TRet> SEHGuarded(std::string_view name, TFunc&& func)
{
	__try
	{
		return func();
	}
	__except (_FilterSEHException(name, GetExceptionCode(), GetExceptionInformation()))
	{
		return std::nullopt;
	}
}

struct _unwrap_optional_tag {};

template <typename TFunc, typename TRet = typename std::invoke_result_t<TFunc>::value_type>
std::optional<TRet> SEHGuarded(_unwrap_optional_tag, std::string_view name, TFunc&& func)
{
	if (auto result = SEHGuarded<TFunc, TRet>(name, std::move(func)))
		return *result;

	return std::nullopt;
}
