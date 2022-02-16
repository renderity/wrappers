#include <cstddef> // size_t
#include <cstring>

#include "wrappers/src/scene/scene.h"



namespace RDTY::WRAPPERS
{
	struct SceneOffsets
	{
		size_t vertex_data = offsetof(Scene, vertex_data);
		size_t index_data = offsetof(Scene, index_data);
	};

	SceneOffsets scene_offsets {};



	void Scene::addObject (Object& object)
	{
		object.scene_vertex_data_offset = vertex_data.size() / 3;
		object.scene_vertex_data_length = object.vertex_data.size() / 3;

		size_t asd = vertex_data.size();

		vertex_data.resize(vertex_data.size() + object.vertex_data.size());

		memcpy(vertex_data.data() + asd, object.vertex_data.data(), object.vertex_data.size() * 4);



		object.scene_index_data_offset = index_data.size();
		object.scene_index_data_length = object.index_data.size();

		size_t asd2 = index_data.size();

		index_data.resize(index_data.size() + object.index_data.size());

		memcpy(index_data.data() + asd2, object.index_data.data(), object.index_data.size() * 4);
	}

	void Scene::addObject (Object* object)
	{
		object->scene_vertex_data_offset = vertex_data.size() / 3;
		object->scene_vertex_data_length = object->vertex_data.size() / 3;

		size_t asd = vertex_data.size();

		vertex_data.resize(vertex_data.size() + object->vertex_data.size());

		memcpy(vertex_data.data() + asd, object->vertex_data.data(), object->vertex_data.size() * 4);



		object->scene_index_data_offset = index_data.size();
		object->scene_index_data_length = object->index_data.size();

		size_t asd2 = index_data.size();

		index_data.resize(index_data.size() + object->index_data.size());

		memcpy(index_data.data() + asd2, object->index_data.data(), object->index_data.size() * 4);
	}
}
