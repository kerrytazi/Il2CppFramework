#pragma once

#include "System/Object.hpp"
#include "System/primitives.hpp"

namespace System { class String; }

namespace UnityEngine
{

class Object : public System::Object
{
public:

	__autogen System::String* get_name();
	__autogen System::Void set_name(System::String* value);
};

} // namespace UnityEngine
