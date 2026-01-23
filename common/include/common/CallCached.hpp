#pragma once

#include <type_traits>
#include <optional>

template <typename TFunc>
class CallCachedStorage
{
public:

	using value_type = std::remove_reference_t<std::invoke_result_t<TFunc>>;

	value_type& Deref()
	{
		CheckInit();
		return *value_;
	}

private:

	void CheckInit()
	{
		if (!value_.has_value()) [[unlikely]]
			value_ = TFunc{}();
	}

	std::optional<value_type> value_;
};

template <typename TFunc>
auto CallCached()
{
	CallCachedStorage<TFunc> storage;
	return storage.Deref();
}
