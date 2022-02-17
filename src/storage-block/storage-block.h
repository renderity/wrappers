#ifndef __RDTY_WRAPPERS_STORAGE_BLOCK__
#define __RDTY_WRAPPERS_STORAGE_BLOCK__



#include <cstddef> // size_t
#include <string>
#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/descriptor-binding-type/descriptor-binding-type.h"



namespace RDTY::WRAPPERS
{
	struct StorageBlock : public Base
	{
		static std::vector<StorageBlock*> instances;

		static void destroy (void);



		// No constructors for aggregate type



		DescriptorBindingType type { DescriptorBindingType::STORAGE_BLOCK };

		size_t binding {};

		std::string name {};

		void* data {};

		size_t size {};
	};
}



#endif
