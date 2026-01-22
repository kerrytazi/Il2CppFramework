#pragma once

#include "System/Object.hpp"

namespace System::Threading
{

class WaitCallback;

class __autogen ThreadPool : System::Object
{
public:

	__autogen static System::Boolean QueueUserWorkItem(System::Threading::WaitCallback* callBack);
};

} // namespace System::Threading
