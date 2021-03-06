#include <cstddef> // size_t
#include <cstring>
#include <algorithm>

#include "wasm-wrapper/src/wasm-log.h"
#include "wrappers/src/scene/scene.h"



namespace RDTY::WRAPPERS
{
	struct SceneOffsets
	{
		size_t position_data { offsetof(Scene, position_data) };
		size_t normal_data { offsetof(Scene, normal_data) };
		size_t index_data { offsetof(Scene, index_data) };
		size_t objects { offsetof(Scene, objects) };
		size_t boxes { offsetof(Scene, boxes) };
		size_t triangles { offsetof(Scene, triangles) };
	};

	SceneOffsets scene_offsets {};



	// void Scene::addObject (Object& object)
	// {
	// 	object.scene_vertex_data_offset = position_data.size() / 3;
	// 	object.scene_vertex_data_length = object.position_data.size() / 3;

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
	// 	object->scene_vertex_data_offset = position_data.size() / 3;
	// 	object->scene_vertex_data_length = object->position_data.size() / 3;

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



	// 	object.scene_vertex_data_offset = position_data.size() / 4;
	// 	object.scene_vertex_data_length = object.position_data.size() / 4;

	// 	position_data.resize(object.scene_vertex_data_offset * 4 + object.scene_vertex_data_length * 4);

	// 	// memcpy(position_data.data() + object.scene_vertex_data_offset * 4, object.position_data.data(), object.scene_vertex_data_length * 4 * 4);



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



	// 	object->scene_vertex_data_offset = position_data.size();
	// 	object->scene_vertex_data_length = object->position_data.size();

	// 	// position_data.resize(object->scene_vertex_data_offset + object->scene_vertex_data_length);

	// 	// memcpy(position_data.data() + object->scene_vertex_data_offset, object->position_data.data(), object->scene_vertex_data_length * 4);



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

			object->scene_vertex_data_offset = position_data_size;
			object->scene_vertex_data_length = object->position_data.size();

			index_data_size += object->scene_index_data_length;
			position_data_size += object->scene_vertex_data_length;
		}

		index_data.resize(index_data_size);
		position_data.resize(position_data_size);
		normal_data.resize(position_data_size);

		for (Object* object : _objects)
		{
			object->scene_index = objects.size();

			memcpy(index_data.data() + object->scene_index_data_offset, object->index_data.data(), object->scene_index_data_length * sizeof(uint32_t));

			if (object != _objects[0])
			{
				for (size_t i { object->scene_index_data_offset }, i_max { object->scene_index_data_offset + object->scene_index_data_length }; i < i_max; i += 4)
				{
					size_t offset { object->scene_vertex_data_offset / 4 };

					index_data[i + 0] += offset;
					index_data[i + 1] += offset;
					index_data[i + 2] += offset;
				}
			}

			memcpy(position_data.data() + object->scene_vertex_data_offset, object->position_data.data(), object->scene_vertex_data_length * sizeof(float));
			memcpy(normal_data.data() + object->scene_vertex_data_offset, object->normal_data.data(), object->scene_vertex_data_length * sizeof(float));

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

	void vsub (__m128& target, const __m128& a, const __m128& b)
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

	bool testPointInsideBox (const __m128& point, const __m128& min, const __m128& max)
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

	bool testRayBoxIntersectionSimd (const __m128& ray_origin, const __m128& ray_direction, const __m128& box_min, const __m128& box_max)
	{
		__m128 t_min = _mm_div_ps(_mm_sub_ps(box_min, ray_origin), ray_direction);
		__m128 t_max = _mm_div_ps(_mm_sub_ps(box_max, ray_origin), ray_direction);

		__m128 min = _mm_min_ps(t_min, t_max);
		__m128 max = _mm_max_ps(t_min, t_max);

		float t_near = std::max(std::max(min[0], min[1]), min[2]);
		float t_far = std::min(std::min(max[0], max[1]), max[2]);

		if (t_near > t_far)
		{
			return false;
		}

		__m128 intersection = _mm_add_ps(_mm_mul_ps(ray_direction, _mm_load_ps1(&t_near)), ray_origin);

		__m128 qwe = _mm_sub_ps(intersection, ray_origin);

		float dot = (ray_direction[0] * qwe[0]) + (ray_direction[1] * qwe[1]) + (ray_direction[2] * qwe[2]);

		return dot > 0.0f;
	}

	bool Scene::testTriangleSimd (const size_t& triangle_index, const __m128& min, const __m128& max, PSIMD* p)
	{
		const size_t vertex1_index { index_data[triangle_index + 0] };
		const size_t vertex2_index { index_data[triangle_index + 1] };
		const size_t vertex3_index { index_data[triangle_index + 2] };

		p->p1 = _mm_load_ps(&position_data[vertex1_index * 4]);
		p->p2 = _mm_load_ps(&position_data[vertex2_index * 4]);
		p->p3 = _mm_load_ps(&position_data[vertex3_index * 4]);

		p->p1p2 = _mm_sub_ps(p->p2, p->p1);
		p->p1p3 = _mm_sub_ps(p->p3, p->p1);

		p->p2p1 = _mm_sub_ps(p->p1, p->p2);
		p->p2p3 = _mm_sub_ps(p->p3, p->p2);

		p->p3p1 = _mm_sub_ps(p->p1, p->p3);
		p->p3p2 = _mm_sub_ps(p->p2, p->p3);



		// TODO: test case when there are no triangle points inside box
		// and no triangle edges intersecting box,
		// but triangle surface cuts box.
		//
		// Triangle cuts box if any edge of the box
		// intersects triangle.
		//
		// This test case can be avoided if all geometry
		// triangles entirely fit into geomerty single atomic box.
		if
		(
			// point inside box
			testPointInsideBox(p->p1, min, max) ||
			testPointInsideBox(p->p2, min, max) ||
			testPointInsideBox(p->p3, min, max) ||

			// edge intersects box
			(testRayBoxIntersectionSimd(p->p1, p->p1p2, min, max) && testRayBoxIntersectionSimd(p->p2, p->p2p1, min, max)) ||
			(testRayBoxIntersectionSimd(p->p2, p->p2p3, min, max) && testRayBoxIntersectionSimd(p->p3, p->p3p2, min, max)) ||
			(testRayBoxIntersectionSimd(p->p3, p->p3p1, min, max) && testRayBoxIntersectionSimd(p->p1, p->p1p3, min, max))
		)
		{
			return true;
		}

		return false;
	}

	void Scene::testSimd (Object* object)
	{
		PSIMD p {};

		__m128 _min {};
		__m128 _max {};

		size_t object_length = objects.size();
		size_t object_index = object->scene_index;

		size_t box_index_bounding { (sizeof(boxes) / sizeof(Box)) / object_length * object_index };
		size_t triangles_index { (sizeof(triangles) / sizeof(uint32_t)) / object_length * object_index };

		triangles_index += ((triangles_index % 4) == 0 ? 0 : (4 - (triangles_index % 4)));

		const size_t dimension_segment_count { object->dimension_segment_count };

		const float step { (object->bounding_box_max[0] - object->bounding_box_min[0]) / dimension_segment_count };

		boxes[box_index_bounding].min[0] = object->bounding_box_min[0];
		boxes[box_index_bounding].min[1] = object->bounding_box_min[1];
		boxes[box_index_bounding].min[2] = object->bounding_box_min[2];

		boxes[box_index_bounding].triangle_start = dimension_segment_count;

		boxes[box_index_bounding].max[0] = object->bounding_box_max[0];
		boxes[box_index_bounding].max[1] = object->bounding_box_max[1];
		boxes[box_index_bounding].max[2] = object->bounding_box_max[2];

		boxes[box_index_bounding].triangle_end = 0;

		if (object_index < object_length - 1)
		{
			boxes[box_index_bounding].triangle_end = (sizeof(boxes) / sizeof(Box)) / object_length * (object_index + 1);
		}



		for (size_t x {}; x < dimension_segment_count; ++x)
		{
			for (size_t y {}; y < dimension_segment_count; ++y)
			{
				for (size_t z {}; z < dimension_segment_count; ++z)
				{
					_min[0] = object->bounding_box_min[0] + (step * x);
					_min[1] = object->bounding_box_min[1] + (step * y);
					_min[2] = object->bounding_box_min[2] + (step * z);

					_max[0] = _min[0] + step;
					_max[1] = _min[1] + step;
					_max[2] = _min[2] + step;



					const size_t triangle_start { triangles_index / 4 };

					for (uint32_t i { (uint32_t) object->scene_index_data_offset }, i_max { (uint32_t) (object->scene_index_data_offset + object->scene_index_data_length) }; i < i_max; i += 4)
					{
						if (testTriangleSimd(i, _min, _max, &p))
						{
							triangles[triangles_index++] = index_data[i + 0];
							triangles[triangles_index++] = index_data[i + 1];
							triangles[triangles_index++] = index_data[i + 2];
							triangles[triangles_index++] = 0;
						}
					}

					const size_t triangle_end { triangles_index / 4 };



					const size_t box_index = box_index_bounding + (x * dimension_segment_count * dimension_segment_count) + (y * dimension_segment_count) + z + 1;

					boxes[box_index].min[0] = _min[0];
					boxes[box_index].min[1] = _min[1];
					boxes[box_index].min[2] = _min[2];

					boxes[box_index].triangle_start = triangle_start;

					boxes[box_index].max[0] = _max[0];
					boxes[box_index].max[1] = _max[1];
					boxes[box_index].max[2] = _max[2];

					boxes[box_index].triangle_end = triangle_end;
				}
			}
		}
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

	bool Scene::testTriangle2 (const size_t& triangle_index, float* min, float* max, P* p)
	{
		const size_t vertex1_index { index_data[triangle_index + 0] };
		const size_t vertex2_index { index_data[triangle_index + 1] };
		const size_t vertex3_index { index_data[triangle_index + 2] };

		p->p1[0] = position_data[(vertex1_index * 4) + 0];
		p->p1[1] = position_data[(vertex1_index * 4) + 1];
		p->p1[2] = position_data[(vertex1_index * 4) + 2];

		p->p2[0] = position_data[(vertex2_index * 4) + 0];
		p->p2[1] = position_data[(vertex2_index * 4) + 1];
		p->p2[2] = position_data[(vertex2_index * 4) + 2];

		p->p3[0] = position_data[(vertex3_index * 4) + 0];
		p->p3[1] = position_data[(vertex3_index * 4) + 1];
		p->p3[2] = position_data[(vertex3_index * 4) + 2];

		vsub(p->p1p2, p->p2, p->p1);
		vsub(p->p1p3, p->p3, p->p1);

		vsub(p->p2p1, p->p1, p->p2);
		vsub(p->p2p3, p->p3, p->p2);

		vsub(p->p3p1, p->p1, p->p3);
		vsub(p->p3p2, p->p2, p->p3);

		if
		(
			// point inside box
			testPointInsideBox(p->p1, min, max) ||
			testPointInsideBox(p->p2, min, max) ||
			testPointInsideBox(p->p3, min, max) ||

			// edge intersects box
			(testRayBoxIntersection(p->p1, p->p1p2, min, max) && testRayBoxIntersection(p->p2, p->p2p1, min, max)) ||
			(testRayBoxIntersection(p->p2, p->p2p3, min, max) && testRayBoxIntersection(p->p3, p->p3p2, min, max)) ||
			(testRayBoxIntersection(p->p3, p->p3p1, min, max) && testRayBoxIntersection(p->p1, p->p1p3, min, max))
		)
		{
			return true;
		}

		return false;
	}

	void Scene::test (void)
	{
		size_t box_index_bounding {};
		size_t box_index_bounding_prev {};
		size_t box_index {};

		for (Object* object : objects)
		{
			const size_t dimension_segment_count { object->dimension_segment_count };

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



						const size_t triangle_start { triangle_count / 4 };

						for (uint32_t i { (uint32_t) object->scene_index_data_offset }, i_max { (uint32_t) (object->scene_index_data_offset + object->scene_index_data_length) }; i < i_max; i += 4)
						{
							if (testTriangle(i, min, max))
							{
								// triangles[triangle_count++] = i / 4;

								triangles[triangle_count++] = index_data[i + 0];
								triangles[triangle_count++] = index_data[i + 1];
								triangles[triangle_count++] = index_data[i + 2];
								triangles[triangle_count++] = 0;
							}
						}

						const size_t triangle_end { triangle_count / 4 };



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

	void Scene::test2 (Object* object)
	{
		P p {};

		float _min [3] {};
		float _max [3] {};

		size_t object_length = objects.size();
		size_t object_index = object->scene_index;

		size_t box_index_bounding { (sizeof(boxes) / sizeof(Box)) / object_length * object_index };
		size_t triangles_index { (sizeof(triangles) / sizeof(uint32_t)) / object_length * object_index };

		triangles_index += ((triangles_index % 4) == 0 ? 0 : (4 - (triangles_index % 4)));

		const size_t dimension_segment_count { object->dimension_segment_count };

		const float step { (object->bounding_box_max[0] - object->bounding_box_min[0]) / dimension_segment_count };

		boxes[box_index_bounding].min[0] = object->bounding_box_min[0];
		boxes[box_index_bounding].min[1] = object->bounding_box_min[1];
		boxes[box_index_bounding].min[2] = object->bounding_box_min[2];

		boxes[box_index_bounding].triangle_start = dimension_segment_count;

		boxes[box_index_bounding].max[0] = object->bounding_box_max[0];
		boxes[box_index_bounding].max[1] = object->bounding_box_max[1];
		boxes[box_index_bounding].max[2] = object->bounding_box_max[2];

		boxes[box_index_bounding].triangle_end = 0;

		if (object_index < object_length - 1)
		{
			boxes[box_index_bounding].triangle_end = (sizeof(boxes) / sizeof(Box)) / object_length * (object_index + 1);
		}



		for (size_t x {}; x < dimension_segment_count; ++x)
		{
			for (size_t y {}; y < dimension_segment_count; ++y)
			{
				for (size_t z {}; z < dimension_segment_count; ++z)
				{
					_min[0] = object->bounding_box_min[0] + (step * x);
					_min[1] = object->bounding_box_min[1] + (step * y);
					_min[2] = object->bounding_box_min[2] + (step * z);

					_max[0] = _min[0] + step;
					_max[1] = _min[1] + step;
					_max[2] = _min[2] + step;



					const size_t triangle_start { triangles_index / 4 };

					for (uint32_t i { (uint32_t) object->scene_index_data_offset }, i_max { (uint32_t) (object->scene_index_data_offset + object->scene_index_data_length) }; i < i_max; i += 4)
					{
						if (testTriangle2(i, _min, _max, &p))
						{
							triangles[triangles_index++] = index_data[i + 0];
							triangles[triangles_index++] = index_data[i + 1];
							triangles[triangles_index++] = index_data[i + 2];
							triangles[triangles_index++] = 0;
						}
					}

					const size_t triangle_end { triangles_index / 4 };



					const size_t box_index = box_index_bounding + (x * dimension_segment_count * dimension_segment_count) + (y * dimension_segment_count) + z + 1;

					boxes[box_index].min[0] = _min[0];
					boxes[box_index].min[1] = _min[1];
					boxes[box_index].min[2] = _min[2];

					boxes[box_index].triangle_start = triangle_start;

					boxes[box_index].max[0] = _max[0];
					boxes[box_index].max[1] = _max[1];
					boxes[box_index].max[2] = _max[2];

					boxes[box_index].triangle_end = triangle_end;
				}
			}
		}
	}
}
