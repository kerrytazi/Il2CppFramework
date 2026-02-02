#pragma once

#include "UnityEngine/Behaviour.hpp"

namespace System::Threading { class CancellationTokenSource; }

namespace UnityEngine
{

class __autogen MonoBehaviour : public UnityEngine::Behaviour
{

private:

	System::Threading::CancellationTokenSource* m_CancellationTokenSource;
};

} // namespace UnityEngine
