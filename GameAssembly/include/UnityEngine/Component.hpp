#pragma once

#include "UnityEngine/Object.hpp"

namespace UnityEngine
{

class Transform;
class GameObject;

class Component : public UnityEngine::Object
{
public:

	__autogen UnityEngine::Transform* get_transform();
	__autogen UnityEngine::GameObject* get_gameObject();
};

} // namespace UnityEngine
