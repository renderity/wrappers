#include "wrappers/src/uniform/uniform.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		struct UniformOffsets
		{
			size_t object_addr = offsetof(Uniform, object_addr);
			size_t name = offsetof(Uniform, name);
			size_t block_index = offsetof(Uniform, block_index);
			size_t size = offsetof(Uniform, size);
		};

		UniformOffsets uniform_offsets {};
	}
}
