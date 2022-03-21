#include <cstddef> // size_t
#include <cstring>

#include "wrappers/src/scene/scene.h"



namespace RDTY::WRAPPERS
{
	struct SceneOffsets
	{
		size_t position_data = offsetof(Scene, position_data);
		size_t index_data = offsetof(Scene, index_data);
		size_t objects = offsetof(Scene, objects);
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



	void Scene::addObject (Object& object)
	{
		object.scene_position_data_offset = position_data.size() / 3;
		object.scene_position_data_length = object.position_data.size() / 3;

		size_t asd = position_data.size();

		position_data.resize(position_data.size() + object.position_data.size());

		memcpy(position_data.data() + asd, object.position_data.data(), object.position_data.size() * 4);



		object.scene_index_data_offset = index_data.size();
		object.scene_index_data_length = object.index_data.size();

		size_t asd2 = index_data.size();

		index_data.resize(index_data.size() + object.index_data.size());

		memcpy(index_data.data() + asd2, object.index_data.data(), object.index_data.size() * 4);



		objects.push_back(&object);
	}

	void Scene::addObject (Object* object)
	{
		object->scene_position_data_offset = position_data.size() / 3;
		object->scene_position_data_length = object->position_data.size() / 3;

		size_t asd = position_data.size();

		position_data.resize(position_data.size() + object->position_data.size());

		memcpy(position_data.data() + asd, object->position_data.data(), object->position_data.size() * 4);



		object->scene_index_data_offset = index_data.size();
		object->scene_index_data_length = object->index_data.size();

		size_t asd2 = index_data.size();

		index_data.resize(index_data.size() + object->index_data.size());

		memcpy(index_data.data() + asd2, object->index_data.data(), object->index_data.size() * 4);



		objects.push_back(object);
	}
}
