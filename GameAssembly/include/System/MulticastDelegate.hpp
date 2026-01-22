#pragma once

#include "System/Delegate.hpp"

namespace il2cpp { template <typename T> class Array; }

namespace System
{

class __autogen MulticastDelegate : public System::Delegate
{
private:

	il2cpp::Array<Delegate>* delegates;
};

} // namespace System
