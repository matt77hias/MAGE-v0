#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct ShadedMaterial final {

	public:

		ShadedMaterial(const CombinedShader &shader, const Material &material)
			: m_shader(shader), m_material(material) {}
		ShadedMaterial(const ShadedMaterial &shaded_material) = default;
		~ShadedMaterial() = default;

		ShadedMaterial &operator=(const ShadedMaterial &shaded_material) = default;

		void Render(ID3D11DeviceContext2 &device_context, const World &world, const TransformBuffer &transform_buffer) {
			m_shader.Render(device_context, m_material, world, transform_buffer);
		}

		Material &GetMaterial() {
			return m_material;
		}
		const Material &GetMaterial() const {
			return m_material;
		}

		CombinedShader &GetShader() {
			return m_shader;
		}
		const CombinedShader &GetShader() const {
			return m_shader;
		}

	private:

		CombinedShader m_shader;
		Material m_material;
	};
}