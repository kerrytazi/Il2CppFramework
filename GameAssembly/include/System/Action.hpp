#pragma once

#include "System/MulticastDelegate.hpp"

namespace System
{

template <typename... TArgs>
class Action : public System::MulticastDelegate
{
};

} // namespace System
