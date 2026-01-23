#pragma once

namespace UnityEngine
{

// [Flags]
enum class CameraType
{
	Game = 1,
	SceneView = 2,
	Preview = 4,
	VR = 8,
	Reflection = 16,
};

} // namespace UnityEngine
