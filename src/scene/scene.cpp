// size_t
#include <cstddef>
// memcpy
#include <cstring>

#include "wrappers/src/scene/scene.h"



namespace RDTY
{
	namespace WRAPPERS
	{
		void Scene::addObject (Object& object)
		{
			object.scene_vertex_data_offset = vertex_data.size() / 3;
			object.scene_vertex_data_length = object.vertex_data.size() / 3;

			size_t asd = vertex_data.size();

			vertex_data.resize(vertex_data.size() + object.vertex_data.size());

			memcpy(vertex_data.data() + asd, object.vertex_data.data(), object.vertex_data.size() * 4);
		}

		void Scene::addObject (Object* object)
		{
			object->scene_vertex_data_offset = vertex_data.size() / 3;
			object->scene_vertex_data_length = object->vertex_data.size() / 3;

			size_t asd = vertex_data.size();

			vertex_data.resize(vertex_data.size() + object->vertex_data.size());

			memcpy(vertex_data.data() + asd, object->vertex_data.data(), object->vertex_data.size() * 4);
		}
	}
}
