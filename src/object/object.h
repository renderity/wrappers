#ifndef __RDTY_WRAPPERS_OBJECT__
#define __RDTY_WRAPPERS_OBJECT__



// size_t
#include <cstddef>
// // uint32_t
// #include <cstdint>
#include <vector>

#include "wrappers/src/base/base.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		struct Object : public Base
		{
			size_t scene_vertex_data_offset {};
			size_t scene_vertex_data_length {};

			std::vector<float> vertex_data
			{
				1.0f, 1.0f, 0.0f,
				-1.0f, 1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f,
			};

			// bool indexed;
			// std::vector<uint32_t> index_data;
			// size_t scene_index_data_offset;
			// size_t scene_index_data_length;

			// const float vertex_data [9]
			// {
			// 	-1.0f, -1.0f, 0.0f,

			// 	-1.0f, 1.0f, 0.0f,

			// 	1.0f, 1.0f, 0.0f,
			// };
		};
	}
}



#endif
