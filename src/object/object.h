#ifndef __RDTY_WRAPPERS_OBJECT__
#define __RDTY_WRAPPERS_OBJECT__



#include <cstddef> // size_t
// #include <cstdint>
#include <vector>

#include "wrappers/src/base/base.h"



namespace RDTY::WRAPPERS
{
	struct Object : public Base
	{
		size_t scene_vertex_data_offset {};
		size_t scene_vertex_data_length {};

		std::vector<float> position_data {};
		std::vector<float> normal_data {};

		size_t scene_index_data_offset {};
		size_t scene_index_data_length {};

		std::vector<uint32_t> index_data {};

		float bounding_box_min [3] {};
		float bounding_box_max [3] {};
		size_t dimension_segment_count { 16 };



		Object (void);



		void makeBoundingBox (void);
	};
}



#endif
