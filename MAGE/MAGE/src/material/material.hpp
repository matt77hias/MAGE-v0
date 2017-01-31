#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\vertex_shader.hpp"
#include "shader\pixel_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Material {

	public:

		Material(SharedPtr< VertexShader > vertex_shader, SharedPtr< PixelShader > pixel_shader)
			: m_vertex_shader(vertex_shader), m_pixel_shader(pixel_shader) {}
		Material(const Material &material)
			: m_vertex_shader(material.m_vertex_shader), m_pixel_shader(material.m_pixel_shader) {}
		virtual ~Material() {}

		Material &operator=(const Material &material) {
			m_vertex_shader = material.m_vertex_shader;
			m_pixel_shader  = material.m_pixel_shader;
			return (*this);
		}

	protected:

		SharedPtr< VertexShader > m_vertex_shader;
		SharedPtr< PixelShader > m_pixel_shader;
	};
}