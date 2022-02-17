#include "wrappers/src/storage-block/storage-block.h"



namespace RDTY::WRAPPERS
{
	std::vector<StorageBlock*> StorageBlock::instances;



	void StorageBlock::destroy (void)
	{
		for (size_t i {}; i < StorageBlock::instances.size(); ++i)
		{
			delete StorageBlock::instances[i];
		}
	}



	struct StorageBlockOffsets
	{
		size_t type = offsetof(StorageBlock, type);
		size_t binding = offsetof(StorageBlock, binding);
		size_t name = offsetof(StorageBlock, name);
		size_t data = offsetof(StorageBlock, data);
		size_t size = offsetof(StorageBlock, size);
	};

	StorageBlockOffsets storage_block_offsets {};
}
