#ifndef __RDTY_WRAPPERS_STORAGE_BLOCK__
#define __RDTY_WRAPPERS_STORAGE_BLOCK__



#include <cstddef> // size_t
#include <string>
#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/descriptor-binding/descriptor-binding.h"



namespace RDTY::WRAPPERS
{
	struct StorageBlock : public Base
	{
		static std::vector<StorageBlock*> instances;

		static void destroy (void);



		// No constructors for aggregate type



		DESCRIPTOR_BINDING::Type type { DESCRIPTOR_BINDING::Type::STORAGE_BLOCK };

		size_t binding {};

		std::string name {};

		void* data {};

		size_t size {};

		std::vector<DESCRIPTOR_BINDING::Visibility> visibility
		{
			RDTY::WRAPPERS::DESCRIPTOR_BINDING::Visibility::VERTEX,
			RDTY::WRAPPERS::DESCRIPTOR_BINDING::Visibility::FRAGMENT,
			RDTY::WRAPPERS::DESCRIPTOR_BINDING::Visibility::COMPUTE,
		};
	};
}



#endif
