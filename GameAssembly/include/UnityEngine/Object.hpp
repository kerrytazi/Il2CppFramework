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
	__autogen static System::Void Destroy(UnityEngine::Object* obj);
	__autogen static System::Void DontDestroyOnLoad(UnityEngine::Object* obj);
};

} // namespace UnityEngine
