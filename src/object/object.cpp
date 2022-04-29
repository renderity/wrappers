#include <cstddef> // size_t
#include <cstring>
#include <cmath>
#include <limits>

#include "wrappers/src/object/object.h"



namespace RDTY::WRAPPERS
{
	struct ObjectOffsets
	{
		size_t scene_index = offsetof(Object, scene_index);
		size_t scene_vertex_data_offset = offsetof(Object, scene_vertex_data_offset);
		size_t scene_vertex_data_size = offsetof(Object, scene_vertex_data_size);
		size_t position_data = offsetof(Object, position_data);
		size_t normal_data = offsetof(Object, normal_data);
		size_t scene_index_data_offset = offsetof(Object, scene_index_data_offset);
		size_t scene_index_data_size = offsetof(Object, scene_index_data_size);
		size_t index_data = offsetof(Object, index_data);
		size_t bounding_box_min = offsetof(Object, bounding_box_min);
		size_t bounding_box_max = offsetof(Object, bounding_box_max);
	};

	ObjectOffsets object_offsets {};



	Object::Object (void)
	{
		float inf = std::numeric_limits<float>::infinity();

		bounding_box_min[0] = inf;
		bounding_box_min[1] = inf;
		bounding_box_min[2] = inf;

		bounding_box_max[0] = -inf;
		bounding_box_max[1] = -inf;
		bounding_box_max[2] = -inf;
	}

	void Object::makeBoundingBox (void)
	{
		for (size_t i {}, i_max { position_data.size() }; i < i_max; i += 4)
		{
			if (position_data[i + 0] < bounding_box_min[0])
			{
				bounding_box_min[0] = position_data[i + 0];
			}

			if (position_data[i + 0] > bounding_box_max[0])
			{
				bounding_box_max[0] = position_data[i + 0];
			}

			if (position_data[i + 1] < bounding_box_min[1])
			{
				bounding_box_min[1] = position_data[i + 1];
			}

			if (position_data[i + 1] > bounding_box_max[1])
			{
				bounding_box_max[1] = position_data[i + 1];
			}

			if (position_data[i + 2] < bounding_box_min[2])
			{
				bounding_box_min[2] = position_data[i + 2];
			}

			if (position_data[i + 2] > bounding_box_max[2])
			{
				bounding_box_max[2] = position_data[i + 2];
			}
		}

		const float center [3]
		{
			(bounding_box_min[0] + bounding_box_max[0]) * 0.5f,
			(bounding_box_min[1] + bounding_box_max[1]) * 0.5f,
			(bounding_box_min[2] + bounding_box_max[2]) * 0.5f,
		};

		const float _min { fmax(fmax(abs(bounding_box_min[0] - center[0]), abs(bounding_box_min[1] - center[1])), abs(bounding_box_min[2] - center[2])) };
		const float _max { fmax(fmax(abs(bounding_box_max[0] - center[0]), abs(bounding_box_max[1] - center[1])), abs(bounding_box_max[2] - center[2])) };
		const float __max { fmax(_min, _max) };

		bounding_box_min[0] = center[0] - __max;
		bounding_box_min[1] = center[1] - __max;
		bounding_box_min[2] = center[2] - __max;

		bounding_box_max[0] = center[0] + __max;
		bounding_box_max[1] = center[1] + __max;
		bounding_box_max[2] = center[2] + __max;
	}
}
