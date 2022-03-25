#ifndef __RDTY_WRAPPERS_MATERIAL__
#define __RDTY_WRAPPERS_MATERIAL__



#include <cstddef> // size_t
#include <cstdint>
#include <string>
#include <vector>

#include "wrappers/src/base/base.h"
#include "wrappers/src/uniform/uniform.h"
#include "wrappers/src/uniform-block/uniform-block.h"
#include "wrappers/src/descriptor-set/descriptor-set.h"



namespace RDTY::WRAPPERS
{
	namespace MATERIAL
	{
		enum class Topology : size_t
		{
			TRIANGLES,
			POINTS,
			LINES,
		};

		enum class FrontFace : size_t
		{
			CW,
			CCW,
		};

		enum class BlendEnabled : size_t
		{
			FALSE,
			TRUE,
		};

		enum class BlendOp : size_t
		{
			ADD,
			SUBTRACT,
			REVERSE_SUBTRACT,
			MIN,
			MAX,
		};

		enum class BlendFactor : size_t
		{
			ZERO,
			ONE,
		};
	}



	struct Material : public Base
	{
		static std::vector<Material*> instances;

		static void destroy (void);



		// No constructors for aggregate type



		MATERIAL::Topology topology {};

		MATERIAL::FrontFace front_face {};

		MATERIAL::BlendEnabled blend_enabled {};

		MATERIAL::BlendOp blend_color_op {};
		MATERIAL::BlendFactor blend_color_factor_src {};
		MATERIAL::BlendFactor blend_color_factor_dst {};

		MATERIAL::BlendOp blend_alpha_op {};
		MATERIAL::BlendFactor blend_alpha_factor_src {};
		MATERIAL::BlendFactor blend_alpha_factor_dst {};

		std::string code_vertex_glsl
		{R"(
			#version 460

			#extension GL_ARB_separate_shader_objects : enable

			precision highp int;
			precision highp float;



			#ifdef VULKAN
				#define SET(_set) set = _set,
			#else
				#define SET(_set)
			#endif



			layout (location = 0) in vec3 in_position;

			out gl_PerVertex
			{
				vec4 gl_Position;
			};

			layout (SET(0) binding = 0) uniform Camera
			{
				mat4 projection_matrix;
				mat4 view_matrix;
			} camera;

			layout (SET(0) binding = 1) uniform Camera2
			{
				mat4 view_matrix;
			} camera2;

			void main (void)
			{
				// gl_Position = camera.projection_matrix * camera.view_matrix * camera2.view_matrix * vec4(in_position, 1.0f);
				gl_Position = camera.projection_matrix * camera.view_matrix * vec4(in_position, 1.0f);
				// gl_Position = camera2.view_matrix * vec4(in_position, 1.0f);
			}
		)"};

		std::string code_vertex_glsl100es
		{R"(
			precision highp int;
			precision highp float;

			attribute vec3 in_position;

			uniform mat4 projection_matrix;
			uniform mat4 view_matrix;

			void main (void)
			{
				gl_Position = projection_matrix * view_matrix * vec4(in_position, 1.0);
			}
		)"};

		std::string code_vertex_glsl300es
		{R"(
			#version 300 es

			precision highp int;
			precision highp float;

			layout (location = 0) in vec3 in_position;

			layout (std140) uniform Camera
			{
				mat4 projection_matrix;
				mat4 view_matrix;
			} camera;

			void main (void)
			{
				gl_Position = camera.projection_matrix * camera.view_matrix * vec4(in_position, 1.0f);
			}
		)"};

		std::string code_vertex_wgsl
		{R"(
			struct VertexIn
			{
				[[location(0)]] pos : vec3<f32>;
				[[builtin(vertex_index)]] vi : u32;
			};

			struct VertexOut
			{
				[[builtin(position)]] pos : vec4<f32>;
			};

			struct Camera
			{
				projection_matrix : mat4x4<f32>;
				view_matrix : mat4x4<f32>;
			};

			[[group(0), binding(0)]] var<uniform> camera : Camera;

			struct Dedicated
			{
				w_offset : f32;
			};

			[[group(0), binding(1)]] var<uniform> dedicated : Dedicated;

			[[stage(vertex)]] fn main(input : VertexIn) -> VertexOut
			{
				var output : VertexOut;

				output.pos = camera.projection_matrix * camera.view_matrix * vec4<f32>(input.pos, 1.0 + dedicated.w_offset);

				return output;
			}
		)"};

		std::vector<uint32_t> code_vertex_spirv { 119734787, 65536, 524298, 36, 0, 131089, 1, 393227, 1, 1280527431, 1685353262, 808793134, 0, 196622, 0, 1, 458767, 0, 4, 1852399981, 0, 10, 26, 196611, 2, 460, 262149, 4, 1852399981, 0, 393221, 8, 1348430951, 1700164197, 2019914866, 0, 393222, 8, 0, 1348430951, 1953067887, 7237481, 196613, 10, 0, 262149, 14, 1701667139, 24946, 524294, 14, 0, 1785688688, 1769235301, 1834970735, 1769108577, 120, 393222, 14, 1, 2003134838, 1952542047, 7891314, 262149, 16, 1701667171, 24946, 327685, 26, 1885302377, 1953067887, 7237481, 327752, 8, 0, 11, 0, 196679, 8, 2, 262216, 14, 0, 5, 327752, 14, 0, 35, 0, 327752, 14, 0, 7, 16, 262216, 14, 1, 5, 327752, 14, 1, 35, 64, 327752, 14, 1, 7, 16, 196679, 14, 2, 262215, 16, 34, 0, 262215, 16, 33, 0, 262215, 26, 30, 0, 131091, 2, 196641, 3, 2, 196630, 6, 32, 262167, 7, 6, 4, 196638, 8, 7, 262176, 9, 3, 8, 262203, 9, 10, 3, 262165, 11, 32, 1, 262187, 11, 12, 0, 262168, 13, 7, 4, 262174, 14, 13, 13, 262176, 15, 2, 14, 262203, 15, 16, 2, 262176, 17, 2, 13, 262187, 11, 20, 1, 262167, 24, 6, 3, 262176, 25, 1, 24, 262203, 25, 26, 1, 262187, 6, 28, 1065353216, 262176, 34, 3, 7, 327734, 2, 4, 0, 3, 131320, 5, 327745, 17, 18, 16, 12, 262205, 13, 19, 18, 327745, 17, 21, 16, 20, 262205, 13, 22, 21, 327826, 13, 23, 19, 22, 262205, 24, 27, 26, 327761, 6, 29, 27, 0, 327761, 6, 30, 27, 1, 327761, 6, 31, 27, 2, 458832, 7, 32, 29, 30, 31, 28, 327825, 7, 33, 23, 32, 327745, 34, 35, 10, 12, 196670, 35, 33, 65789, 65592 };

		std::string code_fragment_glsl
		{R"(
			#version 460

			#extension GL_ARB_separate_shader_objects : enable

			precision highp int;
			precision highp float;

			layout (location = 0) out vec4 fragment_color;

			void main (void)
			{
				fragment_color = vec4(0.25f, 1.0f, 0, 1.0f);
			}
		)"};

		std::string code_fragment_glsl100es
		{R"(
			precision highp int;
			precision highp float;

			void main (void)
			{
				gl_FragColor = vec4(0.25, 0, 0, 1.0);
			}
		)"};

		std::string code_fragment_glsl300es
		{R"(
			#version 300 es

			precision highp int;
			precision highp float;

			layout (location = 0) out vec4 fragment_color;

			void main (void)
			{
				fragment_color = vec4(0.25f, 0, 0, 1.0f);
			}
		)"};

		std::string code_fragment_wgsl
		{R"(
			[[stage(fragment)]] fn main() -> [[location(0)]] vec4<f32>
			{
				return vec4<f32>(1.0, 1.0, 0.0, 1.0);
			}
		)"};

		std::vector<uint32_t> code_fragment_spirv { 119734787, 65536, 524298, 14, 0, 131089, 1, 393227, 1, 1280527431, 1685353262, 808793134, 0, 196622, 0, 1, 393231, 4, 4, 1852399981, 0, 9, 196624, 4, 7, 196611, 2, 460, 262149, 4, 1852399981, 0, 393221, 9, 1734439526, 1953391981, 1819239263, 29295, 262215, 9, 30, 0, 131091, 2, 196641, 3, 2, 196630, 6, 32, 262167, 7, 6, 4, 262176, 8, 3, 7, 262203, 8, 9, 3, 262187, 6, 10, 1048576000, 262187, 6, 11, 0, 262187, 6, 12, 1065353216, 458796, 7, 13, 10, 11, 11, 12, 327734, 2, 4, 0, 3, 131320, 5, 196670, 9, 13, 65789, 65592 };

		std::vector<RDTY::WRAPPERS::Uniform*> uniforms {};
		std::vector<RDTY::WRAPPERS::UniformBlock*> uniform_blocks {};
		std::vector<DescriptorSet*> descriptor_sets {};

		// RDTY::WRAPPERS::UniformBlock dedicated_uniform_block {{ .binding = 0, .name = "Dedicated" }};



		// const Uniform& ?
		void injectUniform (RDTY::WRAPPERS::Uniform&);
		void injectUniform (RDTY::WRAPPERS::Uniform&&);
		void injectUniform (RDTY::WRAPPERS::Uniform*);

		void injectUniformBlock (RDTY::WRAPPERS::UniformBlock&);
		void injectUniformBlock (RDTY::WRAPPERS::UniformBlock&&);
		void injectUniformBlock (RDTY::WRAPPERS::UniformBlock*);
	};
}



#endif
