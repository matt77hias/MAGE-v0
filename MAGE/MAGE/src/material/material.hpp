#pragma once

#include "shader\vertex_shader.hpp"
#include "shader\pixel_shader.hpp"

namespace mage {

	class Material {

	public:

		Material(SharedPtr< VertexShader > m_vertex_shader, SharedPtr< PixelShader > m_pixel_shader)
			: m_vertex_shader(m_vertex_shader), m_pixel_shader(m_pixel_shader) {}
		
		virtual ~Material() {}

	protected:

		SharedPtr< VertexShader > m_vertex_shader;
		SharedPtr< PixelShader > m_pixel_shader;
	};
}