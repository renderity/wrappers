#include "wrappers/src/material/material.h"



namespace RDTY::WRAPPERS
{
	struct MaterialOffsets
	{
		size_t topology = offsetof(Material, topology);
		size_t front_face = offsetof(Material, front_face);
		size_t blend_enabled = offsetof(Material, blend_enabled);
		size_t blend_color_op = offsetof(Material, blend_color_op);
		size_t blend_color_factor_src = offsetof(Material, blend_color_factor_src);
		size_t blend_color_factor_dst = offsetof(Material, blend_color_factor_dst);
		size_t blend_alpha_op = offsetof(Material, blend_alpha_op);
		size_t blend_alpha_factor_src = offsetof(Material, blend_alpha_factor_src);
		size_t blend_alpha_factor_dst = offsetof(Material, blend_alpha_factor_dst);
		size_t code_vertex_glsl = offsetof(Material, code_vertex_glsl);
		size_t code_vertex_glsl100es = offsetof(Material, code_vertex_glsl100es);
		size_t code_vertex_glsl300es = offsetof(Material, code_vertex_glsl300es);
		size_t code_vertex_wgsl = offsetof(Material, code_vertex_wgsl);
		size_t code_vertex_spirv = offsetof(Material, code_vertex_spirv);
		size_t code_fragment_glsl = offsetof(Material, code_fragment_glsl);
		size_t code_fragment_glsl100es = offsetof(Material, code_fragment_glsl100es);
		size_t code_fragment_glsl300es = offsetof(Material, code_fragment_glsl300es);
		size_t code_fragment_wgsl = offsetof(Material, code_fragment_wgsl);
		size_t code_fragment_spirv = offsetof(Material, code_fragment_spirv);
		size_t uniforms = offsetof(Material, uniforms);
		size_t uniform_blocks = offsetof(Material, uniform_blocks);
		size_t descriptor_sets = offsetof(Material, descriptor_sets);
		// size_t dedicated_uniform_block = offsetof(Material, dedicated_uniform_block);
	};

	MaterialOffsets material_offsets {};



	std::vector<Material*> Material::instances {};



	// TODO: destroy all dedicated uniforms
	void Material::destroy (void)
	{
		// for (size_t i {}; i < Material::instances.size(); ++i)
		// {
		// 	delete Material::instances[i];
		// }

		for (Material* material : Material::instances)
		{
			delete material;
		}
	}

	void Material::injectUniform (RDTY::WRAPPERS::Uniform& uniform)
	{
		uniforms.push_back(&uniform);
	}

	void Material::injectUniform (RDTY::WRAPPERS::Uniform&& uniform)
	{
		uniforms.push_back(&uniform);
	}

	void Material::injectUniform (RDTY::WRAPPERS::Uniform* uniform)
	{
		uniforms.push_back(uniform);
	}

	void Material::injectUniformBlock (RDTY::WRAPPERS::UniformBlock& uniform_block)
	{
		uniform_blocks.push_back(&uniform_block);
	}

	void Material::injectUniformBlock (RDTY::WRAPPERS::UniformBlock&& uniform_block)
	{
		uniform_blocks.push_back(&uniform_block);
	}

	void Material::injectUniformBlock (RDTY::WRAPPERS::UniformBlock* uniform_block)
	{
		uniform_blocks.push_back(uniform_block);
	}
}
