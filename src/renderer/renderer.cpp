#include "wrappers/src/renderer/renderer.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		struct RendererOffsets
		{
			size_t width { offsetof(Renderer, width) };
			size_t height { offsetof(Renderer, height) };
		};

		RendererOffsets renderer_offsets {};
	}
}
