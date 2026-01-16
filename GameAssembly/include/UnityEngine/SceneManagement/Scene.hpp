#pragma once

#include "common/autogen.hpp"
#include "System/primitives.hpp"
#include "il2cpp/Array.hpp"

namespace UnityEngine { class GameObject; }

namespace UnityEngine::SceneManagement
{

struct Scene
{
	__autogen System::Boolean IsValid();
	__autogen System::String* get_name();
	__autogen System::Boolean get_isLoaded();

	__autogen il2cpp::Array<UnityEngine::GameObject*>* GetRootGameObjects();

	int m_Handle;
};

} // namespace UnityEngine
