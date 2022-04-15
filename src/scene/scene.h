#ifndef __RDTY_WRAPPERS_SCENE__
#define __RDTY_WRAPPERS_SCENE__



#include <cstdint>
#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/object/object.h"



namespace RDTY::WRAPPERS
{
	struct alignas (16) Box
	{
		float min [3] {};

		uint32_t triangle_start {};

		float max [3] {};

		uint32_t triangle_end {};
	};

	struct P
	{
		float p1 [3] {};
		float p2 [3] {};
		float p3 [3] {};
		float p1p2 [3] {};
		float p1p3 [3] {};
		float p2p1 [3] {};
		float p2p3 [3] {};
		float p3p1 [3] {};
		float p3p2 [3] {};
	};



	struct Scene : public Base
	{
		// TODO: rename to position_data
		std::vector<float> position_data {};
		std::vector<float> normal_data {};
		// std::vector<float> color_data {};

		std::vector<uint32_t> index_data {};

		std::vector<Object*> objects {};

		Box boxes [512 * 512] {};
		uint32_t triangles [1024 * 1024 * 2] {};
		size_t triangle_count {};



		// void addObject (Object&);
		// void addObject (Object*);
		// This fails since vector of references is disallowed!
		// void addObjects (std::vector<Object&>);
		void addObjects (std::vector<Object*>);

		bool testTriangle (const size_t&, float*, float*);
		bool testTriangle2 (const size_t&, float*, float*, P*);
		void test (void);
		void test2 (Object*);
	};
}



#endif
