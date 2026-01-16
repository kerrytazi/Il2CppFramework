#pragma once

#include "System/Object.hpp"

namespace il2cpp
{

template <typename T>
class Array : System::Object
{
public:

	size_t Length() const { return bounds ? bounds->length : max_length; }

	const void* Data() const { return &first_val; }
	void* Data() { return &first_val; }

	T& operator[](size_t index)
	{
		assert(index < Length());
		return begin()[index];
	}

	const T& operator[](size_t index) const
	{
		assert(index < Length());
		return begin()[index];
	}

	T* begin() { return (T*)Data(); }
	T* end() { return ((T*)Data()) + Length(); }

	const T* begin() const { return (const T*)Data(); }
	const T* end() const { return ((const T*)Data()) + Length(); }
	const T* cbegin() const { return (const T*)Data(); }
	const T* cend() const { return ((const T*)Data()) + Length(); }

protected:

	using il2cpp_array_size_t = uintptr_t;
	using il2cpp_array_lower_bound_t = int32_t;

	struct Il2CppArrayBounds
	{
		il2cpp_array_size_t length;
		il2cpp_array_lower_bound_t lower_bound;
	};

	/* bounds is NULL for szarrays */
	Il2CppArrayBounds* bounds;
	/* total number of elements of the array */
	il2cpp_array_size_t max_length;
	uint8_t first_val;
};

} // namespace System
