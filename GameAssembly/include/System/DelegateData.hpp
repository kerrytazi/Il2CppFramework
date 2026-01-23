#pragma once

#include "System/Object.hpp"
#include "System/primitives.hpp"

namespace System
{

class Type;
class String;

class __autogen DelegateData : public System::Object
{
private:

	System::Type* target_type; // 0x10
	System::String* method_name; // 0x18
	System::Boolean curried_first_arg; // 0x20
};

} // namespace System
