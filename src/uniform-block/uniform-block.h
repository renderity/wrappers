#ifndef __RDTY_WRAPPERS_UNIFORM_BLOCK__
#define __RDTY_WRAPPERS_UNIFORM_BLOCK__



#include <cstddef> // size_t
#include <string>
#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/uniform/uniform.h"



namespace RDTY::WRAPPERS
{
	enum class DescriptorBindingType : size_t
	{
		UNIFORM_BUFFER,
	};



	// struct DescriptorBinding
	struct UniformBlock : public Base
	{
		static std::vector<UniformBlock*> instances;

		// TODO: destroy all dedicated uniforms
		static void destroy (void);



		// No constructors for aggregate type



		size_t binding {};

		DescriptorBindingType type {};

		std::string name {};

		std::vector<RDTY::WRAPPERS::Uniform*> uniforms {};



		void injectUniform (RDTY::WRAPPERS::Uniform&);
		void injectUniform (RDTY::WRAPPERS::Uniform&&);
		void injectUniform (RDTY::WRAPPERS::Uniform*);
	};
}



#endif
