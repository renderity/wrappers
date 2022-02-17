#ifndef __RDTY_WRAPPERS_UNIFORM_BLOCK__
#define __RDTY_WRAPPERS_UNIFORM_BLOCK__



#include <cstddef> // size_t
#include <string>
#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/uniform/uniform.h"
#include "wrappers/src/descriptor-binding-type/descriptor-binding-type.h"



namespace RDTY::WRAPPERS
{
	// struct DescriptorBinding
	struct UniformBlock : public Base
	{
		static std::vector<UniformBlock*> instances;

		// TODO: destroy all dedicated uniforms
		static void destroy (void);



		// No constructors for aggregate type



		DescriptorBindingType type { DescriptorBindingType::UNIFORM_BLOCK };

		size_t binding {};

		std::string name {};

		std::vector<RDTY::WRAPPERS::Uniform*> uniforms {};



		void injectUniform (RDTY::WRAPPERS::Uniform&);
		void injectUniform (RDTY::WRAPPERS::Uniform&&);
		void injectUniform (RDTY::WRAPPERS::Uniform*);
	};
}



#endif
