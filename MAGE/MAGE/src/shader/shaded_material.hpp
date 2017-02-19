#pragma once

#include "shader\vertex_shader.hpp"
#include "shader\pixel_shader.hpp"
#include "material\material.hpp"

namespace mage {

	class ShadedMaterial {

	public:

		ShadedMaterial(SharedPtr< VertexShader > vertex_shader, SharedPtr< PixelShader > pixel_shader, const Material &material)
			: m_vertex_shader(vertex_shader), m_pixel_shader(pixel_shader), m_material(material) {}
		ShadedMaterial(const ShadedMaterial &shaded_material) = default;
		virtual ~ShadedMaterial() = default;

		ShadedMaterial &operator=(const ShadedMaterial &shaded_material) = default;

		void Update();

		Material &GetMaterial() {
			return m_material;
		}
		const Material &GetMaterial() const {
			return m_material;
		}

	private:

		SharedPtr< VertexShader > m_vertex_shader;
		SharedPtr< PixelShader > m_pixel_shader;
		Material m_material;
	};
}