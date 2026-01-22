#pragma once

#include "System/Object.hpp"
#include "System/primitives.hpp"

namespace System
{

class DelegateData;

namespace Reflection { class MethodInfo; }

class __autogen Delegate : public System::Object
{
private:

	System::IntPtr method_ptr; // 0x10
	System::IntPtr invoke_impl; // 0x18
	System::Object* m_target; // 0x20
	System::IntPtr method; // 0x28
	System::IntPtr delegate_trampoline; // 0x30
	System::IntPtr extra_arg; // 0x38
	System::IntPtr method_code; // 0x40
	System::IntPtr interp_method; // 0x48
	System::IntPtr interp_invoke_impl; // 0x50
	System::Reflection::MethodInfo* method_info; // 0x58
	System::Reflection::MethodInfo* original_method_info; // 0x60
	System::DelegateData* data; // 0x68
	System::Boolean method_is_virtual; // 0x70
};

} // namespace System
