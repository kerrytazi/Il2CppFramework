#pragma once

namespace UnityEngine
{

enum class RenderingPath
{
	UsePlayerSettings = -1,
	VertexLit = 0,
	Forward = 1,
	//[Obsolete("DeferredLighting has been removed. Use DeferredShading, Forward or HDRP/URP instead.", False)]
	DeferredLighting = 2,
	DeferredShading = 3,
};

} // namespace UnityEngine
