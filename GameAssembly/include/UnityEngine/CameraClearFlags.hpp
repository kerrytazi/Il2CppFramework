#pragma once

namespace UnityEngine
{

// [Flags]
enum class CameraClearFlags
{
	Skybox = 1,
	Color = 2,
	SolidColor = 2,
	Depth = 3,
	Nothing = 4,
};

} // namespace UnityEngine
