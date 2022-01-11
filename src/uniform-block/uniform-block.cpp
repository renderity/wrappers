#include "wrappers/src/uniform-block/uniform-block.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		std::vector<UniformBlock*> UniformBlock::instances;



		void UniformBlock::destroy (void)
		{
			for (size_t i {}; i < UniformBlock::instances.size(); ++i)
			{
				delete UniformBlock::instances[i];
			}
		}

		void UniformBlock::injectUniform (RDTY::WRAPPERS::Uniform& uniform)
		{
			uniforms.push_back(&uniform);
		}

		void UniformBlock::injectUniform (RDTY::WRAPPERS::Uniform&& uniform)
		{
			uniforms.push_back(&uniform);
		}

		void UniformBlock::injectUniform (RDTY::WRAPPERS::Uniform* uniform)
		{
			uniforms.push_back(uniform);
		}



		struct UniformBlockOffsets
		{
			size_t binding = offsetof(UniformBlock, binding);
			size_t type = offsetof(UniformBlock, type);
			size_t name = offsetof(UniformBlock, name);
			size_t uniforms = offsetof(UniformBlock, uniforms);
		};

		UniformBlockOffsets uniform_block_offsets {};
	}
}
