#include <cstddef> // size_t
#include <cstring>

#include "wasm-wrapper/src/wasm-log.h"
#include "wrappers/src/scene/scene.h"



namespace RDTY::WRAPPERS
{
	struct SceneOffsets
	{
		size_t position_data { offsetof(Scene, position_data) };
		size_t index_data { offsetof(Scene, index_data) };
		size_t objects { offsetof(Scene, objects) };
		size_t boxes { offsetof(Scene, boxes) };
		size_t triangles { offsetof(Scene, triangles) };
	};

	SceneOffsets scene_offsets {};



	// void Scene::addObject (Object& object)
	// {
	// 	object.scene_position_data_offset = position_data.size() / 3;
	// 	object.scene_position_data_length = object.position_data.size() / 3;

	// 	size_t asd = position_data.size();

	// 	position_data.resize(position_data.size() + object.position_data.size());

	// 	memcpy(position_data.data() + asd, object.position_data.data(), object.position_data.size() * 4);



	// 	object.scene_index_data_offset = index_data.size();
	// 	object.scene_index_data_length = object.index_data.size();

	// 	size_t asd2 = index_data.size();

	// 	index_data.resize(index_data.size() + object.index_data.size());

	// 	memcpy(index_data.data() + asd2, object.index_data.data(), object.index_data.size() * 4);



	// 	objects.push_back(&object);
	// }

	// void Scene::addObject (Object* object)
	// {
	// 	object->scene_position_data_offset = position_data.size() / 3;
	// 	object->scene_position_data_length = object->position_data.size() / 3;

	// 	size_t asd = position_data.size();

	// 	position_data.resize(position_data.size() + object->position_data.size());

	// 	memcpy(position_data.data() + asd, object->position_data.data(), object->position_data.size() * 4);



	// 	object->scene_index_data_offset = index_data.size();
	// 	object->scene_index_data_length = object->index_data.size();

	// 	size_t asd2 = index_data.size();

	// 	index_data.resize(index_data.size() + object->index_data.size());

	// 	memcpy(index_data.data() + asd2, object->index_data.data(), object->index_data.size() * 4);



	// 	objects.push_back(object);
	// }



	// void Scene::addObject (Object& object)
	// {
	// 	object.scene_index_data_offset = index_data.size();
	// 	object.scene_index_data_length = object.index_data.size();

	// 	index_data.resize(object.scene_index_data_offset + object.scene_index_data_length);

	// 	// memcpy(index_data.data() + object.scene_index_data_offset, object.index_data.data(), object.scene_index_data_length * 4);



	// 	for (size_t i { object.scene_index_data_offset }, i_max { object.scene_index_data_offset + object.scene_index_data_length }; i < i_max; i += 4)
	// 	{
	// 		index_data[i + 0] += position_data.size() / 4;
	// 		index_data[i + 1] += position_data.size() / 4;
	// 		index_data[i + 2] += position_data.size() / 4;
	// 	}



	// 	object.scene_position_data_offset = position_data.size() / 4;
	// 	object.scene_position_data_length = object.position_data.size() / 4;

	// 	position_data.resize(object.scene_position_data_offset * 4 + object.scene_position_data_length * 4);

	// 	// memcpy(position_data.data() + object.scene_position_data_offset * 4, object.position_data.data(), object.scene_position_data_length * 4 * 4);



	// 	objects.push_back(&object);
	// }

	// void Scene::addObject (Object* object)
	// {
	// 	object->scene_index_data_offset = index_data.size();
	// 	object->scene_index_data_length = object->index_data.size();

	// 	// index_data.resize(object->scene_index_data_offset + object->scene_index_data_length);

	// 	// memcpy(index_data.data() + object->scene_index_data_offset, object->index_data.data(), object->scene_index_data_length * 4);



	// 	// for (size_t i { object->scene_index_data_offset }, i_max { object->scene_index_data_offset + object->scene_index_data_length }; i < i_max; i += 4)
	// 	// {
	// 	// 	index_data[i + 0] += position_data.size() / 4;
	// 	// 	index_data[i + 1] += position_data.size() / 4;
	// 	// 	index_data[i + 2] += position_data.size() / 4;
	// 	// }



	// 	object->scene_position_data_offset = position_data.size();
	// 	object->scene_position_data_length = object->position_data.size();

	// 	// position_data.resize(object->scene_position_data_offset + object->scene_position_data_length);

	// 	// memcpy(position_data.data() + object->scene_position_data_offset, object->position_data.data(), object->scene_position_data_length * 4);



	// 	objects.push_back(object);
	// }

	void Scene::addObjects (std::vector<Object*> _objects)
	{
		size_t index_data_size {};
		size_t position_data_size {};

		for (Object* object : _objects)
		{
			object->scene_index_data_offset = index_data_size;
			object->scene_index_data_length = object->index_data.size();

			object->scene_position_data_offset = position_data_size;
			object->scene_position_data_length = object->position_data.size();

			index_data_size += object->scene_index_data_length;
			position_data_size += object->scene_position_data_length;
		}

		index_data.resize(index_data_size);
		position_data.resize(position_data_size);

		for (Object* object : _objects)
		{
			memcpy(index_data.data() + object->scene_index_data_offset, object->index_data.data(), object->scene_index_data_length * sizeof(uint32_t));

			if (object != _objects[0])
			{
				for (size_t i { object->scene_index_data_offset }, i_max { object->scene_index_data_offset + object->scene_index_data_length }; i < i_max; i += 4)
				{
					size_t offset { object->scene_position_data_offset / 4 };

					index_data[i + 0] += offset;
					index_data[i + 1] += offset;
					index_data[i + 2] += offset;
				}
			}

			memcpy(position_data.data() + object->scene_position_data_offset, object->position_data.data(), object->scene_position_data_length * sizeof(float));

			objects.push_back(object);
		}
	}



	float p1 [3] {};
	float p2 [3] {};
	float p3 [3] {};
	float p1p2 [3] {};
	float p1p3 [3] {};
	float p2p1 [3] {};
	float p2p3 [3] {};
	float p3p1 [3] {};
	float p3p2 [3] {};

	void vsub (float* target, float* a, float* b)
	{
		target[0] = a[0] - b[0];
		target[1] = a[1] - b[1];
		target[2] = a[2] - b[2];
	}

	bool testPointInsideBox (float* point, float* min, float* max)
	{
		return
		(
			point[0] <= max[0] && point[0] >= min[0] &&
			point[1] <= max[1] && point[1] >= min[1] &&
			point[2] <= max[2] && point[2] >= min[2]
		);
	}

	bool testRayBoxIntersection (float* ray_origin, float* ray_direction, float* box_min, float* box_max)
	{
		float tmin { (box_min[0] - ray_origin[0]) / ray_direction[0] };
		float tmax { (box_max[0] - ray_origin[0]) / ray_direction[0] };

		if (tmin > tmax)
		{
			float _tmp { tmin };
			tmin = tmax;
			tmax = _tmp;
		}

		float tymin { (box_min[1] - ray_origin[1]) / ray_direction[1] };
		float tymax { (box_max[1] - ray_origin[1]) / ray_direction[1] };

		if (tymin > tymax)
		{
			float _tmp { tymin };
			tymin = tymax;
			tymax = _tmp;
		}

		if ((tmin > tymax) || (tymin > tmax))
		{
			return false;
		}

		if (tymin > tmin)
		{
			tmin = tymin;
		}

		if (tymax < tmax)
		{
			tmax = tymax;
		}

		float tzmin { (box_min[2] - ray_origin[2]) / ray_direction[2] };
		float tzmax { (box_max[2] - ray_origin[2]) / ray_direction[2] };

		if (tzmin > tzmax)
		{
			float _tmp { tzmin };
			tzmin = tzmax;
			tzmax = _tmp;
		}

		if ((tmin > tzmax) || (tzmin > tmax))
		{
			return false;
		}

		if (tzmin > tmin)
		{
			tmin = tzmin;
		}

		if (tzmax < tmax)
		{
			tmax = tzmax;
		}

		if (tmin > tmax)
		{
			return false;
		}

		return (tmin > 0 && tmax > 0);
		// return true;
	}

	bool Scene::testTriangle (const size_t& triangle_index, float* min, float* max)
	{
		const size_t vertex1_index { index_data[triangle_index + 0] };
		const size_t vertex2_index { index_data[triangle_index + 1] };
		const size_t vertex3_index { index_data[triangle_index + 2] };

		p1[0] = position_data[(vertex1_index * 4) + 0];
		p1[1] = position_data[(vertex1_index * 4) + 1];
		p1[2] = position_data[(vertex1_index * 4) + 2];

		p2[0] = position_data[(vertex2_index * 4) + 0];
		p2[1] = position_data[(vertex2_index * 4) + 1];
		p2[2] = position_data[(vertex2_index * 4) + 2];

		p3[0] = position_data[(vertex3_index * 4) + 0];
		p3[1] = position_data[(vertex3_index * 4) + 1];
		p3[2] = position_data[(vertex3_index * 4) + 2];

		vsub(p1p2, p2, p1);
		vsub(p1p3, p3, p1);

		vsub(p2p1, p1, p2);
		vsub(p2p3, p3, p2);

		vsub(p3p1, p1, p3);
		vsub(p3p2, p2, p3);

		if
		(
			// point inside box
			testPointInsideBox(p1, min, max) ||
			testPointInsideBox(p2, min, max) ||
			testPointInsideBox(p3, min, max) ||

			// edge intersects box
			(testRayBoxIntersection(p1, p1p2, min, max) && testRayBoxIntersection(p2, p2p1, min, max)) ||
			(testRayBoxIntersection(p2, p2p3, min, max) && testRayBoxIntersection(p3, p3p2, min, max)) ||
			(testRayBoxIntersection(p3, p3p1, min, max) && testRayBoxIntersection(p1, p1p3, min, max))
		)
		{
			return true;
		}

		return false;
	}

	void Scene::test (void)
	{
		const size_t dimension_segment_count { 16 };

		size_t box_index_bounding {};
		size_t box_index_bounding_prev {};
		size_t box_index {};

		for (Object* object : objects)
		{
			float min [3] {};
			float max [3] {};

			const float step { (object->bounding_box_max[0] - object->bounding_box_min[0]) / dimension_segment_count };

			boxes[box_index_bounding].min[0] = object->bounding_box_min[0];
			boxes[box_index_bounding].min[1] = object->bounding_box_min[1];
			boxes[box_index_bounding].min[2] = object->bounding_box_min[2];

			boxes[box_index_bounding].triangle_start = dimension_segment_count;

			boxes[box_index_bounding].max[0] = object->bounding_box_max[0];
			boxes[box_index_bounding].max[1] = object->bounding_box_max[1];
			boxes[box_index_bounding].max[2] = object->bounding_box_max[2];

			boxes[box_index_bounding].triangle_end = 0;

			if (box_index_bounding != 0)
			{
				boxes[box_index_bounding_prev].triangle_end = box_index_bounding;

				box_index_bounding_prev = box_index_bounding;
			}



			for (size_t x {}; x < dimension_segment_count; ++x)
			{
				for (size_t y {}; y < dimension_segment_count; ++y)
				{
					for (size_t z {}; z < dimension_segment_count; ++z)
					{
						min[0] = object->bounding_box_min[0] + (step * x);
						min[1] = object->bounding_box_min[1] + (step * y);
						min[2] = object->bounding_box_min[2] + (step * z);

						max[0] = min[0] + step;
						max[1] = min[1] + step;
						max[2] = min[2] + step;



						const size_t triangle_start { triangle_count };

						for (uint32_t i { object->scene_index_data_offset }, i_max { object->scene_index_data_offset + object->scene_index_data_length }; i < i_max; i += 4)
						{
							if (testTriangle(i, min, max))
							{
								triangles[triangle_count++] = i / 4;
							}
						}

						const size_t triangle_end { triangle_count };



						box_index = box_index_bounding + (x * dimension_segment_count * dimension_segment_count) + (y * dimension_segment_count) + z + 1;

						boxes[box_index].min[0] = min[0];
						boxes[box_index].min[1] = min[1];
						boxes[box_index].min[2] = min[2];

						boxes[box_index].triangle_start = triangle_start;

						boxes[box_index].max[0] = max[0];
						boxes[box_index].max[1] = max[1];
						boxes[box_index].max[2] = max[2];

						boxes[box_index].triangle_end = triangle_end;
					}
				}
			}



			box_index_bounding += (dimension_segment_count * dimension_segment_count * dimension_segment_count) + 1;
		}
	}
}
