#include <cstddef> // size_t
#include <cstring>

#include "wrappers/src/object/object.h"



namespace RDTY::WRAPPERS
{
	struct ObjectOffsets
	{
		size_t scene_vertex_data_offset = offsetof(Object, scene_vertex_data_offset);
		size_t scene_vertex_data_length = offsetof(Object, scene_vertex_data_length);
		size_t vertex_data = offsetof(Object, vertex_data);
		size_t scene_index_data_offset = offsetof(Object, scene_index_data_offset);
		size_t scene_index_data_length = offsetof(Object, scene_index_data_length);
		size_t index_data = offsetof(Object, index_data);
	};

	ObjectOffsets object_offsets {};
}
